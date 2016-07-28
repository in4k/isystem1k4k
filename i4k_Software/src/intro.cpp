//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#include <math.h>
#include "system.h"
#include "fp.h"
#include "main.h"

static unsigned int myLut[XRES*YRES];
static unsigned int myTex[256*256];



void initLut( void )
{
	for( int j=0; j<YRES; j++ )
    for( int i=0; i<XRES; i++ )
    {
        const float x = -1.0f + (float)i*(2.0f/(float)XRES);
        const float y =  1.0f - (float)j*(2.0f/(float)YRES);
        const float r = sqrtf( x*x+y*y );
        const float a = atan2f( y, x );

        const float u = 1.0f/r;
        const float v = a*(3.0f/3.14159f);
              float w = r*r;
        if( w>1.0f ) w=1.0f;

        const int iu = f2i(u*255.0f);
        const int iv = f2i(v*255.0f);
        const int iw = f2i(w*255.0f);

        myLut[XRES*j+i] = ((iw&255)<<16) | ((iv&255)<<8) | (iu&255);
    }
}


void initTexture( void )
{
	for( int j=0; j<256; j++ )
    for( int i=0; i<256; i++ )
    {
        int r = (i ^ j);
        int g = (((i>>6)&1)^((j>>6)&1))*255;
        g = (g*5 + 3*r)>>3;
        myTex[256*j+i] = 0xff000000 | (g<<16) | (g<<8) | g;
    }
}
void intro_init( void )
{
	initTexture();
    initLut();
}


static __forceinline unsigned int colScale( unsigned int col, int sca )
{
    return ((((col&0x00ff00ff)*sca)>>8)&0x00ff00ff) + ((((col&0x0000ff00)*sca)>>8)&0x0000ff00);

}
void intro_do( unsigned int *buffer, long itime )
{
    for( int i=0; i<XRES*YRES; i++ )
    {
        const unsigned int val = myLut[i];
	    const unsigned int col = myTex[ ((val&0x0000ffff)+(itime>>2))&0x0000ffff ];
        buffer[i] = colScale( col, (val>>16) );
    }
}
