//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "intro.h"
#include "main.h"

static D3DPRESENT_PARAMETERS devParams = 
{
    0, 0,   // xres, yres
    D3DFMT_A8R8G8B8, 
    0,      // backBufferCount;
    D3DMULTISAMPLE_4_SAMPLES, 
    0,      // multiSampleQuality;
    D3DSWAPEFFECT_DISCARD, 
    0,      // hDeviceWindow;
    true,   // windowed
    true,
    D3DFMT_D24S8,
    0,  // flags;
    0,  // fullScreen_RefreshRateInHz;
    D3DPRESENT_INTERVAL_IMMEDIATE   // presentationInterval
};

//----------------------------------------------------------------------------

typedef struct
{
    //---------------
    HINSTANCE   hInstance;
    HDC         hDC;
    HGLRC       hRC;
    HWND        hWnd;
    //---------------
    int         full;
    //---------------
    char        wndclass[4];	// window class and title :)
    //---------------
}WININFO;


static WININFO wininfo = {  0,0,0,0,0, {'i','q','_',0} };

#ifdef LOADING
static char fnt_wait[6]    = "arial";
static char msg_wait[22]   = "wait while loading...";
#endif
#ifdef ERRORMSG
static char msg_error[207] = "kinderplomber";
static char tlt_error[6]   = "error";
#endif


//==============================================================================================


static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// salvapantallas
	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )
		return( 0 );

	// boton x o pulsacion de escape
	if( uMsg==WM_CLOSE || uMsg==WM_DESTROY || (uMsg==WM_KEYDOWN && wParam==VK_ESCAPE) )
		{
		PostQuitMessage(0);
        return( 0 );
		}

    if( uMsg==WM_CHAR || uMsg==WM_KEYDOWN)
        {
        if( wParam==VK_ESCAPE )
            {
            PostQuitMessage(0);
            return( 0 );
            }
        }

    return( DefWindowProc(hWnd,uMsg,wParam,lParam) );
}


static void window_end( WININFO *info )
{
    if( info->hDC  ) ReleaseDC( info->hWnd, info->hDC );
    if( info->hWnd ) DestroyWindow( info->hWnd );

    UnregisterClass( info->wndclass, info->hInstance );

    if( info->full )
        {
        ChangeDisplaySettings( 0, 0 );
		while( ShowCursor( 1 )<0 ); // show cursor
        }
}

//-----------------------------------------------
//-----------------------------------------------

static int window_init( WININFO *info )
{
    DWORD			dwExStyle, dwStyle;
    DEVMODE			dmScreenSettings;
    RECT			rec;
    WNDCLASS		wc;

    ZeroMemory( &wc, sizeof(WNDCLASS) );
    wc.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = info->hInstance;
    wc.lpszClassName = info->wndclass;
    wc.hbrBackground=(HBRUSH)CreateSolidBrush(0x00785838);
	
    if( !RegisterClass(&wc) )
        return( 0 );

    if( info->full )
    {
        dmScreenSettings.dmSize       = sizeof(DEVMODE);
        dmScreenSettings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmPelsWidth  = XRES;
        dmScreenSettings.dmPelsHeight = YRES;

        if( ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
            return( 0 );

        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_VISIBLE | WS_POPUP;// | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		while( ShowCursor( 0 )>=0 );	// hide cursor
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }

    rec.left   = 0;
    rec.top    = 0;
    rec.right  = XRES;
    rec.bottom = YRES;

    AdjustWindowRect( &rec, dwStyle, 0 );

    info->hWnd = CreateWindowEx( dwExStyle, wc.lpszClassName, "lumos", dwStyle,
                               (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
                               rec.right-rec.left, rec.bottom-rec.top, 0, 0, info->hInstance, 0 );

    if( !info->hWnd )
        return( 0 );

    info->hDC = GetDC(info->hWnd);
    if( !info->hDC )
        return( 0 );
    
    return( 1 );
}


//==============================================================================================

static void DrawTime( WININFO *info, float t )
{
    static int      frame=0;
    static float    to=0.0;
    static int      fps=0;
    char            str[64];
    int             s, m;


    if( t<0.0f) return;
    if( info->full ) return;

    frame++;
    if( (t-to)>1.0f )
        {
        fps = frame;
        to = t;
        frame = 0;
        }

    if( !(frame&3) )
        {
          
        m = (int)floorf( t/60.0f );
        s = (int)floorf( t-60.0f*(float)m );

        sprintf( str, "%d fps, %02d:%02d", fps, m, s );

        SetWindowText( info->hWnd, str );
        }
}

//==============================================================================================
//==============================================================================================


int WINAPI WinMain( HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    MSG         msg;
    int         done=0;
    WININFO     *info = &wininfo;

	IDirect3DDevice9 *d3dDevice;

	IDirect3D9 *d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !d3d )
		return 0;

    info->hInstance = GetModuleHandle( 0 );

    //if( MessageBox( 0, "fullscreen?", info->wndclass, MB_YESNO|MB_ICONQUESTION)==IDYES ) info->full++;

    if( !window_init(info) )
        {
        window_end( info );
        MessageBox( 0, "window_init()!","error",MB_OK|MB_ICONEXCLAMATION );
        return( 0 );
        }

    devParams.hDeviceWindow = info->hWnd;
    if( d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, devParams.hDeviceWindow,
                           D3DCREATE_HARDWARE_VERTEXPROCESSING, &devParams, &d3dDevice ) < 0 )
        return 0;

    intro_init( d3dDevice );

  
    long to=0;
    while( !done )
    {
		long t = GetTickCount();
        if( !to ) to=t; 
        t-=to;
		
	    while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
        {
            if( msg.message==WM_QUIT ) done=1;
		    TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        intro_do( d3dDevice, t );
        DrawTime( info, .001f*t );
    }

    d3dDevice->Release();
    d3d->Release();
    window_end( info );

    return( 0 );
}
