#ifndef _VEC2_H_
#define _VEC2_H_

#include <math.h>

class vec2
{
public:
	float x, y;

public:
	__forceinline vec2()
	{
	}
	__forceinline vec2( const float v )
	{
		x = v;
		y = v;
	}
	__forceinline vec2( const float a, const float b )
	{
		x = a;
		y = b;
	}
	__forceinline vec2( const float *v )
	{
		x = v[0];
		y = v[1];
	}

	//--------------------------

	__forceinline void operator*=(const float v) 
	{
		x *= v;
		y *= v;
	}

	__forceinline void operator*=(const vec2 & v) 
	{
		x *= v.x;
		y *= v.y;
	}

	#if 0
	__forceinline const vec3 operator*(const vec3 & v) const 
	{
		return vec3(x*v.x,y*v.y,z*v.z);
	}
	#else
	friend __forceinline vec2 operator*(const vec2 & a, const vec2 & b)
	{
		return vec2(a.x*b.x,a.y*b.y);
	}
	#endif

	friend __forceinline vec2 operator*(float b,const vec2 & a)
	{
		return vec2(a.x*b,a.y*b);
	}
	friend __forceinline vec2 operator*(const vec2 & a,float b)
	{
		return vec2(a.x*b,a.y*b);
	}

	//--------------------------

	__forceinline void operator+=(const float v) 
	{
		x += v;
		y += v;
	}

	__forceinline void operator+=(const vec2 &v) 
	{
		x += v.x;
		y += v.y;
	}

	__forceinline const vec2 operator+(const vec2 & v) const 
	{
		return vec2(x+v.x,y+v.y);
	}
/*
	friend __forceinline vec3 operator+(float b,const vec3 & a)
	{
		return vec3(a.x+b,a.y+b,a.z+b);
	}
*/
	//--------------------------

	__forceinline const vec2 operator-(const vec2 & v) const 
	{
		return vec2(x-v.x,y-v.y);
	}

	__forceinline const vec2 operator-(const float v) const 
	{
		return vec2(x-v,y-v);
	}

	//--------------------------

	friend __forceinline vec2 normalize( const vec2 & nor )
	{
		const float im = 1.0f / sqrtf( nor.x*nor.x + nor.y*nor.y );
		return vec2(nor.x*im, nor.y*im);
	}

	friend __forceinline float dot( const vec2 & a, const vec2 & b )
	{
	    return a.x*b.x + a.y*b.y;
	}

	friend __forceinline float length( const vec2 & a )
	{
	    return sqrtf( a.x*a.x + a.y*a.y );
	}

	friend __forceinline vec2 mix( const vec2 & a, const vec2 & b, float f )
	{
	    return vec2( a.x+f*(b.x-a.x), a.y+f*(b.y-a.y) );
	}

	friend __forceinline vec2 clamp( const vec2 & v, float a, float b )
	{
		return vec2((v.x<a)?a:(v.x>b)?b:v.x,
					(v.y<a)?a:(v.y>b)?b:v.y);
	}

	friend __forceinline vec2 abs( const vec2 & v )
	{
		return vec2( fabsf(v.x), fabsf(v.y) );
	}

	/*
	friend __forceinline vec3 max( const vec3 & v, float m )
	{
		return vec3( v.x>m?v.x:m, v.y>m?v.y:m, v.z>m?v.z:m );
	}*/

};




#endif