#version 120
#extension GL_ARB_texture_rectangle : enable

uniform float 			u_time;
uniform float 			u_progress;
uniform vec2 			u_resolution;

#define M_PI 3.1415926535897932384626433832795
#define M_PI_BY_2 (M_PI / 2)
#define M_2_PI (M_PI * 2)
#define M_PI_BY_8 (M_PI / 8)

uniform sampler2DRect tex0;


float circle(vec2 uv,float rad)
{
	return length(uv * rad);
}

vec2 rotate(vec2 uv,float r)
{
	float s = sin(r);
	float c = cos(r);

	mat2 m = mat2(c, -s, s, c);
	return m * uv.xy;
}

void main()
{
	// Screen Space Coordinates
	vec2 uv = gl_FragCoord.xy / u_resolution.xy;

	uv = uv * 2.0 - 1.0;
	
	uv = rotate(uv,u_time*1.0);
	
	uv.x += 1.56;
	float a = sin(uv.x);
	
	uv.y += 1.56;
	float b = sin(uv.y);
	
	float c = cos(uv.x-uv.y);
	
	float d = cos(uv.x+uv.y);
	float amo = 200.0;
	
	a = pow(a,amo);
	b = pow(b,amo);
	c = pow(c,amo);
	d = pow(d,amo);
	
	a += b;
//	a += c;
//	a += d;
	
	gl_FragColor = vec4(a,a,a,1.0);
}

