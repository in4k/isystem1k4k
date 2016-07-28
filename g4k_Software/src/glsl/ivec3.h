#ifndef _IVEC3_H_
#define _IVEC3_H_

class ivec3
{
public:
	int x, y, z;

public:
	__forceinline ivec3()
	{
	}
	__forceinline ivec3( const int v )
	{
		x = v;
		y = v;
		z = v;
	}
	__forceinline ivec3( const int a, const int b, const int c )
	{
		x = a;
		y = b;
		z = c;
	}
	__forceinline ivec3( const int *v )
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}

	//--------------------------

	__forceinline void operator*=(const int v) 
	{
		x *= v;
		y *= v;
		z *= v;
	}

	__forceinline void operator*=(const ivec3 & v) 
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}


	friend __forceinline ivec3 operator*(const ivec3 & a,const ivec3 & b)
	{
		return ivec3(a.x*b.x,a.y*b.y,a.z*b.z);
	}

	friend __forceinline ivec3 operator*(int b,const ivec3 & a)
	{
		return ivec3(a.x*b,a.y*b,a.z*b);
	}

	//--------------------------

	__forceinline void operator+=(const int v) 
	{
		x += v;
		y += v;
		z += v;
	}

	__forceinline void operator+=(const ivec3 &v) 
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	__forceinline const ivec3 operator+(const ivec3 & v) const 
	{
		return ivec3(x+v.x,y+v.y,z+v.z);
	}
/*
	friend __forceinline vec3 operator+(float b,const vec3 & a)
	{
		return vec3(a.x+b,a.y+b,a.z+b);
	}
*/
	//--------------------------

	__forceinline const ivec3 operator-(const ivec3 & v) const 
	{
		return ivec3(x-v.x,y-v.y,z-v.z);
	}

	__forceinline const ivec3 operator-(const int v) const 
	{
		return ivec3(x-v,y-v,z-v);
	}

	//--------------------------

	friend __forceinline ivec3 clamp( const ivec3 & v, int a, int b )
	{
		return ivec3((v.x<a)?a:(v.x>b)?b:v.x,
				 	(v.y<a)?a:(v.y>b)?b:v.y,
				 	(v.z<a)?a:(v.z>b)?b:v.z);
	}

	friend __forceinline ivec3 abs( const ivec3 & v )
	{
		return ivec3( abs(v.x), abs(v.y), abs(v.z) );
	}
/*
	friend __forceinline vec3 max( const vec3 & v, float m )
	{
		return vec3( v.x>m?v.x:m, v.y>m?v.y:m, v.z>m?v.z:m );
	}*/

};




#endif