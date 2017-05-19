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
	vec2 center = u_resolution.xy / 2.0;
	vec2 coord = gl_FragCoord.xy;

	vec2 uv = gl_FragCoord.xy / u_resolution.xy;
	uv = uv * 2.0 - 1.0;
	
	vec2 aspectRatio = vec2(u_resolution.x / u_resolution.y, 1.0);
	
	float time = -u_time * 5.0;
	
	float a = sin(length(uv*aspectRatio * 0.8) * 25.0  + time);
	float b = sin(length(uv*aspectRatio * 0.8) * 25.0  + time);
	float c = sin(length(uv*aspectRatio * 0.8) * 25.0  + time);

	a *= abs(cos(u_time*0.87));
	b *= abs(cos(u_time*0.65));
	c *= abs(cos(u_time*0.15));
	
	gl_FragColor = vec4(a,b,c,1.0);
}

