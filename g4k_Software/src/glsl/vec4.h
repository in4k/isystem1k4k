#ifndef _VEC4_H_
#define _VEC4_H_

#include <math.h>

class vec4
{
public:
	float x, y, z, w;

public:

	__forceinline vec4()
	{
	}
	__forceinline vec4( const float v )
	{
		x = v;
		y = v;
		z = v;
		w = v;
	}
	__forceinline vec4( const float a, const float b, const float c, const float d )
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
	__forceinline vec4( const float *v )
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
	}

	//--------------------------

	__forceinline void operator*=(const float v) 
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
	}

	__forceinline void operator*=(const vec4 & v) 
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
	}

	#if 0
	__forceinline const vec4 operator*(const vec4 & v) const 
	{
		return vec4(x*v.x,y*v.y,z*v.z);
	}
	#else
	friend __forceinline vec4 operator*(const vec4 & a,const vec4 & b)
	{
		return vec4(a.x*b.x,a.y*b.y,a.z*b.z,a.w*b.w);
	}
	#endif

	friend __forceinline vec4 operator*(float b,const vec4 & a)
	{
		return vec4(a.x*b,a.y*b,a.z*b,a.w*b);
	}

	//--------------------------

	__forceinline void operator+=(const float v) 
	{
		x += v;
		y += v;
		z += v;
		w += v;
	}

	__forceinline void operator+=(const vec4 &v) 
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	__forceinline const vec4 operator+(const vec4 & v) const 
	{
		return vec4(x+v.x,y+v.y,z+v.z,w+v.w);
	}
/*
	friend __forceinline vec4 operator+(float b,const vec4 & a)
	{
		return vec4(a.x+b,a.y+b,a.z+b);
	}
*/
	//--------------------------

	__forceinline const vec4 operator-(const vec4 & v) const 
	{
		return vec4(x-v.x,y-v.y,z-v.z,w-v.w);
	}

	__forceinline const vec4 operator-(const float v) const 
	{
		return vec4(x-v,y-v,z-v,w-v);
	}

	__forceinline vec3 xyz( void ) const
	{
		return vec3(x,y,z);
	}

	//--------------------------

	friend __forceinline vec4 normalize( const vec4 & nor )
	{
		const float im = 1.0f / sqrtf( nor.x*nor.x + nor.y*nor.y + nor.z*nor.z + nor.w*nor.w );
		return vec4(nor.x*im, nor.y*im, nor.z*im, nor.w*im);
	}

	friend __forceinline float dot( const vec4 & a, const vec4 & b )
	{
	    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
	}

	friend __forceinline vec4 mix( const vec4 & a, const vec4 & b, float f )
	{
	    return vec4( a.x+f*(b.x-a.x), a.y+f*(b.y-a.y), a.z+f*(b.z-a.z), a.w+f*(b.w-a.w) );
	}

	friend __forceinline vec4 clamp( const vec4 & v, float a, float b )
	{
		return vec4((v.x<a)?a:(v.x>b)?b:v.x,
					(v.y<a)?a:(v.y>b)?b:v.y,
					(v.z<a)?a:(v.z>b)?b:v.z,
					(v.w<a)?a:(v.w>b)?b:v.w);
	}

	friend __forceinline vec4 abs( const vec4 & v )
	{
		return vec4( fabsf(v.x), fabsf(v.y), fabsf(v.z), fabsf(v.w) );
	}
/*
	friend __forceinline vec4 max( const vec4 & v, float m )
	{
		return vec4( v.x>m?v.x:m, v.y>m?v.y:m, v.z>m?v.z:m );
	}*/

};




#endif