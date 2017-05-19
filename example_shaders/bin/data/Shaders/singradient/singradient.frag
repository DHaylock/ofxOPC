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

void main()
{
	// Screen Space Coordinates
	vec2 uv = gl_FragCoord.xy / u_resolution.xy;

	uv = uv * 2.0 - 1.0;
//	uv.x += 1.5;
	
//	uv.x = uv.x + sin(u_time);
//	float a = sin(uv.x);
	float b = cos(uv.y) * sin(u_time);
	float c = uv.y*0.5;
	
//	a = pow(a,50.0);
	
//	a += b;
	
//	uv.x = sin(uv.x * 0.5);
//	uv.y = cos(uv.y * 0.5);
	float a = (atan(uv.y,uv.x) / (M_PI*4.0)) - sin(u_time);// * 1.2;
	gl_FragColor = vec4(a,a,a,1.0);
}

