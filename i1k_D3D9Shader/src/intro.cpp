//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "fp.h"

//------------------------------------------------------------------------------------------------------------------

static const float quadVerts[4*5] =
{
  1.0f,-1.0f,0.0f,1.0f,0.0f,
 -1.0f,-1.0f,0.0f,0.0f,0.0f,
  1.0f, 1.0f,0.0f,1.0f,1.0f,
 -1.0f, 1.0f,0.0f,0.0f,1.0f
};

static const char shaderCode[] = \

"float4 ps_main(float2 u:texcoord):color"
"{"
    "return float4(u.x,u.y,0.4,1);"
"}";

//------------------------------------------------------------------------------------------------------------------

static IDirect3DPixelShader9  *gShader;

//------------------------------------------------------------------------------------------------------------------

void intro_init( IDirect3DDevice9 *d3dDevice )
{
    ID3DXBuffer *tmp;
    #ifndef DEBUG
    D3DXCompileShader( shaderCode, sizeof(shaderCode)-1, 0, 0, "ps_main", "ps_2_0", D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXSHADER_PREFER_FLOW_CONTROL, &tmp, 0, 0 );
    #else
    ID3DXBuffer *errors;
    if( D3DXCompileShader( shaderCode, sizeof(shaderCode)-1, 0, 0, "ps_main", "ps_2_0", D3DXSHADER_DEBUG*0+1*(D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXSHADER_PREFER_FLOW_CONTROL), &tmp, &errors, 0 ) <0 )
    {
        OutputDebugString( (char*)errors->GetBufferPointer() );
        errors->Release();
        DebugBreak();
    }
    #endif
    d3dDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &gShader );
}

void intro_do( IDirect3DDevice9 *d3dDevice, long time )
{
    const float t = (float)time / 1000.0f;

    d3dDevice->BeginScene();
    d3dDevice->SetPixelShader( gShader );
    d3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_TEX1 );
    d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,quadVerts,5*sizeof(float));
    d3dDevice->EndScene();
    d3dDevice->Present( NULL, NULL, NULL, NULL );
}