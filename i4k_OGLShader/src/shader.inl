//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//
static const char *vsh = \
"#version 430\n"

"layout (location=0) in vec2 inVer;"
"out vec2 p;"
"out gl_PerVertex"
"{"
"vec4 gl_Position;"
"};"
"void main()"
"{"
    "gl_Position=vec4(inVer,0.0,1.0);"
    "p=inVer;"
"}";

static const char * fsh = \
"#version 430\n"

"layout (location=0) uniform vec4 fpar[4];"
"layout (location=0) out vec4 co;"
"in vec2 p;"

"float iSphere(in vec3 ro, in vec3 rd, in vec4 sph)"
"{"
    "vec3  q = ro - sph.xyz;"
    "float b = dot( q, rd );"
    "float c = dot( q, q ) - sph.w*sph.w;"
    "float h = b*b - c;"
    "if( h>0.0 ) h = -b - sqrt( h );"
	"return h;"
"}"

"void main()"
"{"
    "vec3 w=normalize(fpar[1].xyz-fpar[0].xyz);"
    "vec3 u=normalize(cross(w,vec3(0.0,1.0,0.0)));"
    "vec3 v=cross(u,w);"

    "vec3 ro = fpar[0].xyz;"
    "vec3 rd = normalize( p.x*u*1.77 + p.y*v + 0.75*w );"

    "float dif = dot( p, vec2(0.707) );"

    "float t = iSphere(ro,rd,fpar[2]);"
    "if(t>0.0)"
    "{"
        "vec3 pos = ro + t*rd;"
        "vec3 nor = normalize( pos - fpar[2].xyz );"
        "dif = dot(nor,vec3(0.57703));"
    "}"
    "co = dif*vec4(0.5,0.4,0.3,0.0) + vec4(0.5,0.5,0.5,1.0);"
"}";
