//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <d3d9.h>
#include "intro.h"
#include "main.h"

static D3DPRESENT_PARAMETERS devParams = {
    XRES, YRES, D3DFMT_A8R8G8B8, 0, D3DMULTISAMPLE_NONE,
    0, D3DSWAPEFFECT_DISCARD, 0, false, true,
    D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_IMMEDIATE };

#ifdef DEBUG
extern "C" int _fltused = 0;
#endif

void entrypoint( void )
{    
	IDirect3DDevice9 *d3dDevice;

	IDirect3D9 *d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !d3d )
		return;

    devParams.hDeviceWindow = CreateWindow("static",0,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
    if( d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,devParams.hDeviceWindow,D3DCREATE_HARDWARE_VERTEXPROCESSING,&devParams,&d3dDevice )<0)
        return;

    ShowCursor( 0 );  

    intro_init( d3dDevice );
    do 
    {
        intro_do( d3dDevice, GetTickCount() );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );

    ExitProcess(0);
    #ifdef CLEANEXIT
    d3dDevice->Release();
    d3d->Release();
    DestroyWindow( devParams.hDeviceWindow );
    #endif
}

