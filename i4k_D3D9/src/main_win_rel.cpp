//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
//typedef unsigned long * DWORD_PTR;
#include <d3d9.h>
#ifdef USEDSOUND
#include <dsound.h>
#endif

#include "main.h"
#include "intro.h"
#include "mzk.h"

static D3DPRESENT_PARAMETERS devParams = {
    XRES, YRES, D3DFMT_A8R8G8B8, 0, D3DMULTISAMPLE_NONE,
    0, D3DSWAPEFFECT_DISCARD, 0, false, true,
    D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_IMMEDIATE };

#ifdef DEBUG
extern "C" int _fltused = 0;
#endif
#ifdef USEDSOUND
static WAVEFORMATEX format={WAVE_FORMAT_PCM, MZK_NUMCHANNELS, MZK_RATE, MZK_RATE*MZK_NUMCHANNELS*sizeof(short), MZK_NUMCHANNELS*sizeof(short), 8*sizeof(short)};       
static DSBUFFERDESC bufferDesc1={sizeof(DSBUFFERDESC), DSBCAPS_PRIMARYBUFFER};
static DSBUFFERDESC bufferDesc2={sizeof(DSBUFFERDESC), DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS, MZK_NUMSAMPLESC*sizeof(short), NULL, &format, NULL };
#else
static const int wavHeader[11] = {
    0x46464952, 
    MZK_NUMSAMPLES*2+36, 
    0x45564157, 
    0x20746D66, 
    16, 
    WAVE_FORMAT_PCM|(MZK_NUMCHANNELS<<16), 
    MZK_RATE, 
    MZK_RATE*MZK_NUMCHANNELS*sizeof(short), 
    (MZK_NUMCHANNELS*sizeof(short))|((8*sizeof(short))<<16),
    0x61746164, 
    MZK_NUMSAMPLES*sizeof(short)
    };
static short myMuzik[MZK_NUMSAMPLESC+22];
#endif

void entrypoint( void )
{    
	IDirect3DDevice9 *d3dDevice;

	IDirect3D9 *d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !d3d )
		return;

    devParams.hDeviceWindow = CreateWindow( "static",0,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
    if( d3d->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,devParams.hDeviceWindow,D3DCREATE_HARDWARE_VERTEXPROCESSING,&devParams,&d3dDevice) < 0 )
        return;

    ShowCursor( 0 );

    intro_init( d3dDevice );

    #ifdef USEDSOUND
    short                *myMuzik;
    unsigned long        length;
    LPDIRECTSOUNDBUFFER  m_pSecondary;
    LPDIRECTSOUND        m_pDS;
    LPDIRECTSOUNDBUFFER  m_pPrimary;
    DirectSoundCreate(0, &m_pDS, 0);
    m_pDS->SetCooperativeLevel(devParams.hDeviceWindow,DSSCL_PRIORITY);
    m_pDS->CreateSoundBuffer(&bufferDesc1,&m_pPrimary, NULL);
    m_pDS->CreateSoundBuffer(&bufferDesc2,&m_pSecondary,NULL);
    m_pPrimary->SetFormat(&format);
    m_pSecondary->Lock(0,MZK_NUMSAMPLESC*sizeof(short),(void**)&myMuzik,&length,NULL,NULL,NULL);
    #endif


    // calculate music
    mzk_init(myMuzik);
    // and play it 

    #ifdef USEDSOUND
    m_pSecondary->Unlock(myMuzik,length,NULL,NULL);
    m_pSecondary->Play(0,0,0);
    #else
    memcpy( myMuzik, wavHeader, 44 );
    sndPlaySound( (const char*)&myMuzik, SND_ASYNC|SND_MEMORY );
    long to = timeGetTime();
    long t = 65535;
    #endif

    // main loop
    do 
    {
        #ifdef USEDSOUND
        unsigned long t;
        m_pSecondary->GetCurrentPosition(&t,NULL);
        t = 10*t/882;
        #else
        t = timeGetTime()-to; 
        #endif
        intro_do( d3dDevice, t );
    }while ( !GetAsyncKeyState(VK_ESCAPE) );

    #ifndef USEDSOUND
    sndPlaySound(0,0);
    #endif

    #ifdef CLEANEXIT
    d3dDevice->Release();
    d3d->Release();
    DestroyWindow( devParams.hDeviceWindow );
    #endif

    ExitProcess(0);
}

