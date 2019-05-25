//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "main.h"
#include "glext.h"
#include "fragmentShader.inl"

//----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" 
{
#endif
int  _fltused = 0;
#ifdef __cplusplus
}
#endif

static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32, 0, 0, 0, 0, 0, 0, 
    0,  0, 0, 0, 0, 0, 0,
    32, 
    0, 
    0,
    PFD_MAIN_PLANE,
    0, 0, 0, 0 };

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



//----------------------------------------------------------------------------

void entrypoint( void )
{
    // full screen
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return; ShowCursor( 0 );
    // create window
    HDC hDC = GetDC(CreateWindow( "static",0,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0));
    // initalize opengl
    SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd);
    wglMakeCurrent(hDC,wglCreateContext(hDC));

    // init intro
    const unsigned int vsId = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_VERTEX_SHADER,   1, &vertexShader);
    const unsigned int fsId = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_FRAGMENT_SHADER, 1, &fragmentShader);
    unsigned int pid;
	((PFNGLGENPROGRAMPIPELINESPROC)wglGetProcAddress("glGenProgramPipelines"))(1, &pid);
    ((PFNGLBINDPROGRAMPIPELINEPROC)wglGetProcAddress("glBindProgramPipeline"))(pid);
    ((PFNGLUSEPROGRAMSTAGESPROC)wglGetProcAddress("glUseProgramStages"))(pid, GL_VERTEX_SHADER_BIT, vsId);
    ((PFNGLUSEPROGRAMSTAGESPROC)wglGetProcAddress("glUseProgramStages"))(pid, GL_FRAGMENT_SHADER_BIT, fsId);

    do 
    {
        glRects( -1, -1, 1, 1 );
        wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE ); //SwapBuffers( hDC );
		Sleep(50);
    }while ( !GetAsyncKeyState(VK_ESCAPE) );

    ChangeDisplaySettings( 0, 0 );
    ShowCursor(1);

    ExitProcess(0);
}
