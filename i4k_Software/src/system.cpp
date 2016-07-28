//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008/2015                                   //
//--------------------------------------------------------------------------//

#ifdef WINDOWS

int f2i(float x) // use this to convert float to int, or use /QIfist as additional compiler parameters
{
    int tmp;
    _asm fld dword ptr[x]
    _asm fistp dword ptr[tmp];
    return tmp;
}

float mpowf(float a, float b)
{
	float res;
	_asm fld			dword ptr [b]
	_asm fld			dword ptr [a]
	_asm fyl2x
	_asm fld			st
	_asm frndint
	_asm fsub		st(1),st
	_asm fxch		st(1)
	_asm f2xm1
	_asm fld1
	_asm fadd
	_asm fscale
	_asm fstp		st(1)
	_asm fstp dword ptr [res]
	return res;
}

float mfmodf( float x, float y )
{
	float res;
	_asm fld dword ptr [y]
	_asm fld dword ptr [x]
	_asm fprem
	_asm fstp st(1);
	_asm fstp dword ptr [res]
	return res;
}

float m2xf(float f)
{
    _asm fld   dword ptr [f]
    _asm fld1
    _asm fld   st(1)
    _asm fprem
    _asm f2xm1
    _asm faddp st(1), st
    _asm fscale
    _asm fstp  st(1)
    _asm fstp  dword ptr [f]
    return f;
}

int mifloorf( float x )
{
	x = x - 0.5f;
    int t;
    _asm fld x
    _asm fistp t
    return t;
}

#endif