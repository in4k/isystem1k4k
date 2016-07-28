//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "glext.h"
#include "main.h"
#include "fragmentShader.inl"
#include "vertexShader.inl"

//=================================================================================================================


#ifdef DEBUG
#define NUMFUNCIONES 11

static float fparams[4*4];
static void *myglfunc[NUMFUNCIONES];

static const char *strs[] = {
	"glCreateProgram",
	"glCreateShader",
	"glShaderSource",
	"glCompileShader",
	"glAttachShader",
	"glLinkProgram",
	"glUseProgram",
    "glUniform4fv",
    "glGetUniformLocation",
	"glGetObjectParameterivARB",
	"glGetInfoLogARB" };

#define oglCreateProgram	            ((PFNGLCREATEPROGRAMPROC)myglfunc[0])
#define oglCreateShader		            ((PFNGLCREATESHADERPROC)myglfunc[1])
#define oglShaderSource                 ((PFNGLSHADERSOURCEPROC)myglfunc[2])
#define oglCompileShader                ((PFNGLCOMPILESHADERPROC)myglfunc[3])
#define oglAttachShader                 ((PFNGLATTACHSHADERPROC)myglfunc[4])
#define oglLinkProgram                  ((PFNGLLINKPROGRAMPROC)myglfunc[5])
#define oglUseProgram                   ((PFNGLUSEPROGRAMPROC)myglfunc[6])
#define oglUniform4fv                   ((PFNGLUNIFORM4FVPROC)myglfunc[7])
#define oglGetUniformLocation           ((PFNGLGETUNIFORMLOCATIONARBPROC)myglfunc[8])
#define oglGetObjectParameteriv         ((PFNGLGETOBJECTPARAMETERIVARBPROC)myglfunc[9])
#define oglGetInfoLog                   ((PFNGLGETINFOLOGARBPROC)myglfunc[10])

int intro_compute( void )
{
    for( int i=0; i<NUMFUNCIONES; i++ )
    {
        #ifdef WIN32
        myglfunc[i] = wglGetProcAddress( strs[i] );
        #endif
        #ifdef LINUX
        myglfunc[i] = glXGetProcAddress( (const unsigned char *)strs[i] );
        #endif
        if( !myglfunc[i] )
			return( 0 );
    }

    int pid = oglCreateProgram();                           
	const int vsId = oglCreateShader( GL_VERTEX_SHADER ); 
	const int fsId = oglCreateShader( GL_FRAGMENT_SHADER );
	oglShaderSource( vsId, 1, &vertexShader, 0 );
	oglShaderSource( fsId, 1, &fragmentShader, 0 );
    oglCompileShader( vsId );
    oglCompileShader( fsId );
	oglAttachShader( pid, fsId );
	oglAttachShader( pid, vsId );
	oglLinkProgram( pid );

	int		result;
    char    info[1024];
    oglGetObjectParameteriv( vsId, GL_OBJECT_COMPILE_STATUS_ARB, &result ); oglGetInfoLog( vsId, 1024, NULL, (char *)info ); if( !result ) DebugBreak();
    oglGetObjectParameteriv( fsId, GL_OBJECT_COMPILE_STATUS_ARB, &result ); oglGetInfoLog( fsId, 1024, NULL, (char *)info ); if( !result ) DebugBreak();
    oglGetObjectParameteriv( pid,  GL_OBJECT_LINK_STATUS_ARB,    &result ); oglGetInfoLog( pid,  1024, NULL, (char *)info ); if( !result ) DebugBreak();

	fparams[ 0] = 0.0f;
    fparams[ 1] = 0.0f;
    fparams[ 2] = 0.0f;
    fparams[ 3] = 0.0f;
    fparams[ 4] = 0.0f;
    fparams[ 5] = 0.0f;
    fparams[ 6] = 0.0f;
    fparams[ 7] = 0.0f;

    oglUseProgram( pid );
    oglUniform4fv( oglGetUniformLocation( pid, "fpar" ),  4, fparams );
    glRects( -1, -1, 1, 1 );

	return 1;
}

#else


int intro_compute( void )
{
    int pid = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
	const int vsId = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_VERTEX_SHADER);
	const int fsId = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);	
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(vsId, 1, &vertexShader, 0);
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(fsId, 1, &fragmentShader, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(vsId);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(fsId);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(pid,vsId);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(pid,fsId);
    ((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(pid);
    ((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(pid);

    glRects( -1, -1, 1, 1 );

	return 1;
}

#endif