//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include "intro.h"
#include "main.h"

//----------------------------------------------------------------------------

static const BITMAPINFO bmi = {{sizeof(BITMAPINFOHEADER),XRES,-YRES,1,32,BI_RGB,0,0,0,0,0},{0,0,0,0}};

static DEVMODE screenSettings = { {0},
    #if _MSC_VER < 1400
    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
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

extern "C" { int _fltused = 0; }

//----------------------------------------------------------------------------

static unsigned int buffer[XRES*YRES] = { 0 };

//----------------------------------------------------------------------------

void entrypoint( void )
{
    #ifdef ISFULLSCREEN
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return;
    ShowCursor( 0 );
    #endif

    HDC hDC = GetDC( CreateWindowEx( WS_EX_TOPMOST, "static", 0, WS_VISIBLE|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0, 0, XRES, YRES, 0, 0, 0, 0 ) );

    intro_init();

    long to = timeGetTime();
    do
    {
        
        intro_do( buffer, timeGetTime()-to );
	    StretchDIBits(hDC,0,0,XRES,YRES,0,0,XRES,YRES,buffer,&bmi,DIB_RGB_COLORS,SRCCOPY);
    }while( !GetAsyncKeyState(VK_ESCAPE));

    ExitProcess(0);
}
