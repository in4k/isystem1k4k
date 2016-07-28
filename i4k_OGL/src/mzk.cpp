//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#include <math.h>
#include "mzk.h"
#include "system.h"



// put here your synth
void mzk_init( short *buffer )
{
    for( int i=0; i<MZK_NUMSAMPLES; i++ ) 
    {
        const float fl = sinf( 6.2831f*440.0f * (float)i/(float)MZK_RATE );
        const float fr = sinf( 6.2831f*587.3f * (float)i/(float)MZK_RATE );
        buffer[2 * i + 0] = f2i(fl*32767.0f);
        buffer[2 * i + 1] = f2i(fr*32767.0f);
    }
}
