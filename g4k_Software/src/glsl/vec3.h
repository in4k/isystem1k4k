#ifndef _VEC3_H_
#define _VEC3_H_

#include <math.h>

class vec3
{
public:
	float x, y, z;

public:
	__forceinline vec3()
	{
	}
	__forceinline vec3( const float v )
	{
		x = v;
		y = v;
		z = v;
	}
	__forceinline vec3( const float a, const float b, const float c )
	{
		x = a;
		y = b;
		z = c;
	}
	__forceinline vec3( const float *v )
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}

	//--------------------------

	__forceinline void operator*=(const float v) 
	{
		x *= v;
		y *= v;
		z *= v;
	}

	__forceinline void operator*=(const vec3 & v) 
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	#if 0
	__forceinline const vec3 operator*(const vec3 & v) const 
	{
		return vec3(x*v.x,y*v.y,z*v.z);
	}
	#else
	friend __forceinline vec3 operator*(const vec3 & a, const vec3 & b)
	{
		return vec3(a.x*b.x,a.y*b.y,a.z*b.z);
	}
	#endif

	friend __forceinline vec3 operator*(float b,const vec3 & a)
	{
		return vec3(a.x*b,a.y*b,a.z*b);
	}
	friend __forceinline vec3 operator*(const vec3 & a,float b)
	{
		return vec3(a.x*b,a.y*b,a.z*b);
	}

	friend __forceinline vec3 operator/(const vec3 & a,float b)
	{
		return vec3(a.x/b,a.y/b,a.z/b);
	}
	//--------------------------

	__forceinline void operator+=(const float v) 
	{
		x += v;
		y += v;
		z += v;
	}

	__forceinline void operator+=(const vec3 &v) 
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	__forceinline const vec3 operator+(const vec3 & v) const 
	{
		return vec3(x+v.x,y+v.y,z+v.z);
	}
/*
	friend __forceinline vec3 operator+(float b,const vec3 & a)
	{
		return vec3(a.x+b,a.y+b,a.z+b);
	}
*/
	//--------------------------

	__forceinline const vec3 operator-(const vec3 & v) const 
	{
		return vec3(x-v.x,y-v.y,z-v.z);
	}

	__forceinline const vec3 operator-(const float v) const 
	{
		return vec3(x-v,y-v,z-v);
	}

	//--------------------------

	friend __forceinline vec3 normalize( const vec3 & nor )
	{
		const float im = 1.0f / sqrtf( nor.x*nor.x + nor.y*nor.y + nor.z*nor.z );
		return vec3(nor.x*im, nor.y*im, nor.z*im);
	}

	friend __forceinline float dot( const vec3 & a, const vec3 & b )
	{
	    return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	friend __forceinline float length( const vec3 & a )
	{
	    return sqrtf( a.x*a.x + a.y*a.y + a.z*a.z );
	}

	friend __forceinline vec3 mix( const vec3 & a, const vec3 & b, float f )
	{
	    return vec3( a.x+f*(b.x-a.x), a.y+f*(b.y-a.y), a.z+f*(b.z-a.z) );
	}

	friend __forceinline vec3 clamp( const vec3 & v, float a, float b )
	{
		return vec3((v.x<a)?a:(v.x>b)?b:v.x,
					(v.y<a)?a:(v.y>b)?b:v.y,
					(v.z<a)?a:(v.z>b)?b:v.z);
	}

	friend __forceinline vec3 abs( const vec3 & v )
	{
		return vec3( fabsf(v.x), fabsf(v.y), fabsf(v.z) );
	}

	/*
	friend __forceinline vec3 max( const vec3 & v, float m )
	{
		return vec3( v.x>m?v.x:m, v.y>m?v.y:m, v.z>m?v.z:m );
	}*/

};




#endif