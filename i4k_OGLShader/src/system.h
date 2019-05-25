//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include "glext.h"

extern void *myglfunc[];

#define oglCreateShaderProgramv         ((PFNGLCREATESHADERPROGRAMVPROC)myglfunc[0])
#define oglGenProgramPipelines          ((PFNGLGENPROGRAMPIPELINESPROC)myglfunc[1])
#define oglBindProgramPipeline          ((PFNGLBINDPROGRAMPIPELINEPROC)myglfunc[2])
#define oglUseProgramStages             ((PFNGLUSEPROGRAMSTAGESPROC)myglfunc[3])
#define oglProgramUniform4fv            ((PFNGLPROGRAMUNIFORM4FVPROC)myglfunc[4])

#ifdef DEBUG
#define oglGetProgramiv          ((PFNGLGETPROGRAMIVPROC)myglfunc[5])
#define oglGetProgramInfoLog     ((PFNGLGETPROGRAMINFOLOGPROC)myglfunc[6])
#endif

static inline int f2i(float x) // use this to convert float to int, or use /QIfist as additional compiler parameters
{
    int tmp;
    _asm fld dword ptr[x]
    _asm fistp dword ptr[tmp];
    return tmp;
}

#endif