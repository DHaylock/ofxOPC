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
	float a = circle(uv,7.0*tan(u_time*0.8));
	
	a = 1.0 - pow(a,0.75);
	gl_FragColor = vec4(a,a,a,1.0);
}

