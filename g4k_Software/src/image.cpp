//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#include <math.h>
#include "fp.h"
#include "main.h"
#include "system.h"
#include "glsl/ivec3.h"
#include "glsl/vec2.h"
#include "glsl/vec3.h"
#include "glsl/vec4.h"

static inline float clamp01(float x)
{
    if (x<0.0f) return 0.0f;
    if (x>1.0f) return 1.0f;
    return x;
}

static inline float smoothstep(float x, float a, float b)
{
    if (x<a) return 0.0f;
    if (x>b) return 1.0f;
    x = (x - a) / (b - a);
    return x*x*(3.0f - 2.0f*x);
}

static float interesctSphere(const vec3 & rO, const vec3 & rD, const vec4 & sph)
{
    vec3 p = rO - sph.xyz();
    float b = dot( p, rD );
    float c = dot( p, p ) - sph.w*sph.w;
    float h = b*b - c;
    if( h>0.0f )
    {
        h = -b - sqrtf( h );
    }
	return h;
}

static float interesctFloor(const vec3 & rO, const vec3 & rD)
{
	return -rO.y/rD.y;
}

static void calcColor( vec3 & outputColor, const vec2 & fragment )
{
	vec3 wrd = normalize(vec3(fragment.x*1.77f,fragment.y,-1.0f));
	vec3 wro = vec3(0.0f,1.0f,1.8f);
	vec4 sphere = vec4(0.0f,1.0f,0.0f,1.0f);

	bool didHit = false;
	float t = 1e20f;
	float amb = 0.0f;

	// floor
	float t1 = interesctFloor(wro,wrd);
	if( t1>0.0f && t1<t )
	{
		t = t1;
		didHit = true;
        vec3 pos = wro + t1*wrd;
		amb = 0.8f*smoothstep(sqrtf( pos.x*pos.x + pos.z*pos.z ), 0.0f, 2.0f);
	}

	// sphere
	float t2 = interesctSphere(wro,wrd,sphere);
    if( t2>0.0f && t2<t )
    {
		t = t2;
		didHit = true;
        vec3  pos = wro + t2*wrd;
        vec3  nor = (pos - sphere.xyz())/sphere.w;
		float fre = 1.0f+dot(nor,wrd); fre = fre*fre; fre = fre*fre;
		amb = clamp01( 0.5f + 0.5f*nor.y + fre*0.1f );
    }

	// 
	if( didHit )
	{
		 outputColor = mix( vec3(amb), vec3(1.0f), 1.0f-m2xf(-0.05f*t) );
	}
	else
	{
		outputColor = vec3(1.0f);
	}
}

//=====================================================================================

void image_init( void )
{
}

void image_compute_fragment( float *rgb, float x, float y )
{
	vec3 rgbv;
	calcColor(rgbv,vec2(x,y));
	rgb[0] = rgbv.x;
	rgb[1] = rgbv.y;
	rgb[2] = rgbv.z;
}