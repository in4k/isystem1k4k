//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>
#include <d3dx9math.h>

#include "intro.h"
#include "mzk.h"
#include "fp.h"

//---------------------------------------------------------------------

typedef struct 
{
    float x, y, z;
    DWORD color;
}MyVertexPosDif;

//---------------------------------------------------------------------

#define p0d001 0.00099945068359375f

static const float projectionMatrix[16] = {
    p1d25, 0.0f,   0.0f,   0.0f,
    0.0f,  p1d66,  0.0f,   0.0f,
    0.0f,  0.0f,  -1.0f,  -1.0f,
    0.0f,  0.0f,-p0d001,   0.0f };

static const float identityMatrix[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f };

static const float cameraMatrix[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f, 1.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 1.0f, 0.0f,
                                        0.0f, 0.0f,-4.0f, 1.0f };

static D3DMATERIAL9 materials[] = {

    { { p0d55,  p0d55,  p0d55, 0.0f},   // diffuse
      { p0d20,  p0d25,  p0d30, 0.0f},   // ambient
      { 0.0f,   0.0f,   0.0f,  0.0f},   // specular
      { p0d00,  p0d00,  p0d00, 0.0f},   // emmisive
      0.0f },                           // power

};

static float cubevdata[] = {
 -1.0f, -1.0f, -1.0f,
 -1.0f, -1.0f,  1.0f,
  1.0f, -1.0f,  1.0f,
  1.0f, -1.0f, -1.0f,

  1.0f,  1.0f, -1.0f,
  1.0f,  1.0f,  1.0f,
 -1.0f,  1.0f,  1.0f,
 -1.0f,  1.0f, -1.0f,

 -1.0f,  1.0f, -1.0f,
 -1.0f,  1.0f,  1.0f,
 -1.0f, -1.0f,  1.0f,
 -1.0f, -1.0f, -1.0f,

  1.0f, -1.0f, -1.0f,
  1.0f, -1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f,  1.0f, -1.0f,

  1.0f, -1.0f, -1.0f,
  1.0f,  1.0f, -1.0f,
 -1.0f,  1.0f, -1.0f,
 -1.0f, -1.0f, -1.0f,

 -1.0f, -1.0f,  1.0f,
 -1.0f,  1.0f,  1.0f,
  1.0f,  1.0f,  1.0f,
  1.0f, -1.0f,  1.0f,
};


static int cubeidata[] = { 
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    4, 6, 7,
    8, 9,10,
    8,10,11,
   12,13,14,
   12,14,15,
   16,17,18,
   16,18,19,
   20,21,22,
   20,22,23 };


//------------------------------------------------------------------------------------------------------------------

static ID3DXMesh *gDxMesh;

//------------------------------------------------------------------------------------------------------------------


void intro_init( IDirect3DDevice9 *d3dDevice )
{
    D3DXCreateMeshFVF( 12, 24, D3DXMESH_MANAGED|D3DXMESH_32BIT, D3DFVF_XYZ|D3DFVF_NORMAL, d3dDevice, &gDxMesh );

    float         *vdata;
    unsigned int  *idata;
    gDxMesh->LockVertexBuffer( 0, (void**)&vdata );
    gDxMesh->LockIndexBuffer(  0, (void**)&idata );

    for( int i=0; i<24; i++ )
    {
        vdata[6*i+0] = cubevdata[3*i+0];
        vdata[6*i+1] = cubevdata[3*i+1];
        vdata[6*i+2] = cubevdata[3*i+2];
    }
    for( int i=0; i<12; i++ )
    {
        idata[3*i+0] = cubeidata[3*i+0];
        idata[3*i+1] = cubeidata[3*i+1];
        idata[3*i+2] = cubeidata[3*i+2];
    }

    gDxMesh->UnlockIndexBuffer();
    gDxMesh->UnlockVertexBuffer();

    D3DXComputeNormals( gDxMesh, 0 );
}

void intro_do( IDirect3DDevice9 *d3dDevice, unsigned long time )
{
    const float t = (float)time / 1000.0f;

    // animate
    D3DXMATRIX mat;
    D3DXMatrixRotationYawPitchRoll( &mat, 1.2f*t, 2.0f*t, 1.7f*t );

    // rendefr
    d3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 0x000000, 1.0f, 0);
    d3dDevice->BeginScene();

    d3dDevice->SetTransform( D3DTS_PROJECTION, (const D3DMATRIX*)projectionMatrix );
    d3dDevice->SetTransform( D3DTS_VIEW,       (const D3DMATRIX*)cameraMatrix );
    d3dDevice->SetTransform( D3DTS_WORLD,      (const D3DMATRIX*)identityMatrix );
    d3dDevice->SetRenderState( D3DRS_ZENABLE,  true );
    d3dDevice->SetRenderState( D3DRS_LIGHTING, true );
    d3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    d3dDevice->SetRenderState( D3DRS_SPECULARENABLE, true );
    d3dDevice->LightEnable(0, true); // true

    d3dDevice->SetTransform( D3DTS_WORLD, &mat );
    d3dDevice->SetMaterial( materials+0 );

    gDxMesh->DrawSubset( 0 );

    d3dDevice->EndScene();
    d3dDevice->Present( NULL, NULL, NULL, NULL );
}