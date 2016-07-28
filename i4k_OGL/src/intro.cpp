//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "intro.h"
#include "mzk.h"
#include "fp.h"

//---------------------------------------------------------------------

#define fzn  0.005f
#define fzf  1000.0f

static const float projectionmatrix[16] = {
    1.0f, 0.00f,  0.0f,                    0.0f,
    0.0f, 1.25f,  0.0f,                    0.0f,
    0.0f, 0.00f, -(fzf+fzn)/(fzf-fzn),    -1.0f,
    0.0f, 0.00f, -2.0f*fzf*fzn/(fzf-fzn),  0.0f };

static const float cubeVerts[] = { 

  1.0f, -1.0f, -1.0f,    0.0f,-1.0f, 0.0f,
  1.0f, -1.0f,  1.0f,    0.0f,-1.0f, 0.0f,
 -1.0f, -1.0f,  1.0f,    0.0f,-1.0f, 0.0f,
 -1.0f, -1.0f, -1.0f,    0.0f,-1.0f, 0.0f,

 -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,
 -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,
  1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,
  1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f,

 -1.0f, -1.0f, -1.0f,   -1.0f, 0.0f, 0.0f,
 -1.0f, -1.0f,  1.0f,   -1.0f, 0.0f, 0.0f,
 -1.0f,  1.0f,  1.0f,   -1.0f, 0.0f, 0.0f,
 -1.0f,  1.0f, -1.0f,   -1.0f, 0.0f, 0.0f,

  1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f,
  1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f,
  1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,
  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,

 -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,-1.0f,
 -1.0f,  1.0f, -1.0f,    0.0f, 0.0f,-1.0f,
  1.0f,  1.0f, -1.0f,    0.0f, 0.0f,-1.0f,
  1.0f, -1.0f, -1.0f,    0.0f, 0.0f,-1.0f,

  1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f,
  1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,
 -1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,
 -1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f };

static const int cubeIndices[] = { 
 0, 1, 2, 3,
 4, 5, 6, 7,
 8, 9,10,11,
12,13,14,15,
16,17,18,19,
20,21,22,23 };

//----------------------------------------

int intro_init( void )
{
	return 1;
}



void intro_do( long itime )
{
    const float ftime = 0.001f*(float)itime;

    // animate
    float pos[3] = { 3.0f*cosf(ftime*p1d00), 
                     3.0f*cosf(ftime*p0d60), 
                     3.0f*sinf(ftime*p1d00) };
    float tar[3] = { 0.0f, 0.0f, 0.0f };

    // render
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
	glDisable( GL_BLEND );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_NORMALIZE );

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( projectionmatrix );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( pos[0], pos[1], pos[2], tar[0], tar[1], tar[2], 0.0f, 1.0f, 0.0f );

    // draw cube
    glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 6*sizeof(float), cubeVerts+0);
    glNormalPointer(    GL_FLOAT, 6*sizeof(float), cubeVerts+3);
	glDrawElements( GL_QUADS, 6*4, GL_UNSIGNED_INT, cubeIndices );
	glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
}

