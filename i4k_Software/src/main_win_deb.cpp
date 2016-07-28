//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//



#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include "intro.h"
#include "main.h"

//----------------------------------------------------------------------------

static const BITMAPINFO bmi = {{sizeof(BITMAPINFOHEADER),XRES,-YRES,1,32,BI_RGB,0,0,0,0,0},{0,0,0,0}};

static DEVMODE screenSettings = { {0},
    #if _MSC_VER < 1400
    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0, 2003
    #else
    0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
    #endif
    #if(WINVER >= 0x0400)
    0,0,0,0,0,0,
    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    0,0
    #endif
    #endif
    };


static unsigned int buffer[XRES*YRES];
//----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd = CreateWindowEx( WS_EX_APPWINDOW|WS_EX_WINDOWEDGE, "edit", "expelliamus", 
                                WS_VISIBLE|WS_CAPTION|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 
                                0, 0, XRES, YRES, 0, 0, 0, 0 );

    HDC hdc = GetDC( hwnd );

    intro_init();

    bool done = false;
    long to = timeGetTime();
    while( !done )
    {
        MSG msg; 
        while( PeekMessage( &msg,0,0,0,PM_REMOVE ) ) 
        {
            done |= (GetAsyncKeyState(VK_ESCAPE)!=0);
            DispatchMessage( &msg );
        }
        intro_do( buffer, timeGetTime()-to );
        StretchDIBits(hdc,0,0,XRES,YRES,0,0,XRES,YRES,buffer,&bmi,DIB_RGB_COLORS,SRCCOPY);
        Sleep(1);    // give some time to other processes
    }

    ReleaseDC( hwnd, hdc );
    DestroyWindow( hwnd );

    ExitProcess(0);
}
