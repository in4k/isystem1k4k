//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "glext.h"


//--------------------------------------------------------------------------//
#define XRES 1280
#define YRES  720

#include "shader.h"

const static PIXELFORMATDESCRIPTOR pfd = {0,0,PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


const static char *funcNames[] = { "glCreateProgram",
                                   "glCreateShader",
                                   "glShaderSource",
                                   "glCompileShader",
                                   "glAttachShader",
                                   "glLinkProgram",
                                   "glUseProgram" };

static void *funcPtrs[7];

#define oglCreateProgram ((PFNGLCREATEPROGRAMPROC)funcPtrs[0])
#define oglCreateShader  ((PFNGLCREATESHADERPROC)funcPtrs[1])
#define oglShaderSource  ((PFNGLSHADERSOURCEPROC)funcPtrs[2])
#define oglCompileShader ((PFNGLCOMPILESHADERPROC)funcPtrs[3])
#define oglAttachShader  ((PFNGLATTACHSHADERPROC)funcPtrs[4])
#define oglLinkProgram   ((PFNGLLINKPROGRAMPROC)funcPtrs[5])
#define oglUseProgram    ((PFNGLUSEPROGRAMPROC)funcPtrs[6])


static RECT rec = { 0, 0, XRES, YRES };

//--------------------------------------------------------------------------//
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

    if( uMsg==WM_CHAR )
        {
        if( wParam==VK_ESCAPE )
            {
            PostQuitMessage(0);
            return( 0 );
            }
        }

    return( DefWindowProc(hWnd,uMsg,wParam,lParam) );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
    WNDCLASS		wc;

    // create window
    ZeroMemory( &wc, sizeof(WNDCLASS) );
    wc.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hPrevInstance;
    wc.lpszClassName = "iq";

    if( !RegisterClass(&wc) )
        return( 0 );

    const int dws = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    AdjustWindowRect( &rec, dws, 0 );
    HWND hWnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, wc.lpszClassName, "accio", dws,
                               (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
                               rec.right-rec.left, rec.bottom-rec.top, 0, 0, hPrevInstance, 0 );
    if( !hWnd )
        return( 0 );

    HDC hDC=GetDC(hWnd);
    if( !hDC )
        return( 0 );

    // init opengl
    int pf = ChoosePixelFormat(hDC,&pfd);
    if( !pf )
        return( 0 );
    
    if( !SetPixelFormat(hDC,pf,&pfd) )
        return( 0 );

    HGLRC hRC = wglCreateContext(hDC);
    if( !hRC )
        return( 0 );

    if( !wglMakeCurrent(hDC,hRC) )
        return( 0 );

    // init extensions
    for( int i=0; i<(sizeof(funcPtrs)/sizeof(void*)); i++ )
    {
        funcPtrs[i] = wglGetProcAddress( funcNames[i] );
        if( !funcPtrs[i] )
            return 0;
    }

    // create shader
    int p = oglCreateProgram();
//    int v = oglCreateShader(GL_VERTEX_SHADER);
//    oglShaderSource(v, 1, &vertexShader, 0);
//    oglCompileShader(v);
//    oglAttachShader(p,v);
    int f = oglCreateShader(GL_FRAGMENT_SHADER);	
    oglShaderSource(f, 1, &fragmentShader, 0);
    oglCompileShader(f);
    oglAttachShader(p,f);
    oglLinkProgram(p);
    oglUseProgram(p);
    ShowCursor(0); 

    // run
/*
    do
    { 
        glColor3f(t,sinf(.25f*t),0.0f);
        glRects(-1,-1,1,1);
        SwapBuffers(hDC); //wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );
*/
    int done = 0;
    while( !done )
    {
        const float t = .0025f*(float)(GetTickCount()&65535);

        MSG msg;
        while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
        {
            if( msg.message==WM_QUIT ) done=1;
		    TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        glColor3f(t,sinf(.25f*t),0.0f);
        glRects(-1,-1,1,1);
        SwapBuffers( hDC );
    }

    ExitProcess( 0 );

    return 0;
}
