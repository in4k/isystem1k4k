//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//


#include <windows.h>

#include "image.h"
#include "main.h"
#include "system.h"

#define TILESIZE	8

typedef struct
{
    void *mutex;
	long *tileID;
}ThreadData;

static float fbuffer[IXRES*IYRES*3];

static unsigned long __stdcall doWord( void *vdata )
{
    ThreadData *data = (ThreadData*)vdata;

    WaitForSingleObject( (HANDLE*)data->mutex, 0 );

	const int numtiles = IXRES/TILESIZE;
	for(;;)
	{
		const int tile = InterlockedIncrement( data->tileID ) - 1;
		if( tile >= numtiles ) break;
		const int ia = tile*TILESIZE;
		const int ib = ia + TILESIZE;
		for( int i=ia; i<ib; i++ )
		for( int j=0; j<IYRES; j++ )
		{
			image_compute_fragment( fbuffer+3*(IXRES*j+i), -1.0f+2.0f*(float)i/(float)IXRES, 1.0f-2.0f*(float)j/(float)IYRES );
		}
	}

    ReleaseSemaphore( (HANDLE*)data->mutex, 1, NULL );

    return 1;
}

void intro_compute( unsigned int *ibuffer, int numCpus )
{
    //--------------------------
    ThreadData idata[128];
    HANDLE     th[128];
    HANDLE     barrier;

	__declspec(align(32)) long tileID = 0;

 	image_init();

    //--------------------------

    if( numCpus>128 ) numCpus=128;

	barrier = CreateSemaphore( 0, numCpus, numCpus, 0 );

	for( int i=0; i<numCpus; i++ )
    {
	    unsigned long thid;
        idata[i].mutex = barrier;
		idata[i].tileID = &tileID;
        th[i] = CreateThread( 0, 0, doWord, idata+i, 0, &thid );
    }

    // synch point
    WaitForMultipleObjects(numCpus, th, true, INFINITE);
    // free resources (yes!)
    for( int i=0; i<numCpus; i++ ) CloseHandle(th[i]);
    CloseHandle(barrier);

    //--------------------------
	// float 2 int
    //--------------------------
	for( int i=0; i<(IXRES*IYRES); i++ )
	{
		const int ir = f2i( fbuffer[3*i+0]*255.0f );
        const int ig = f2i( fbuffer[3*i+1]*255.0f );
        const int ib = f2i( fbuffer[3*i+2]*255.0f );
		ibuffer[i] = 0xff000000 | (ir<<16) | (ig<<8) | ib;
	}
}