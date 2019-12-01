#version 450 core

out vec4 FragColor;

uniform int u_ScreenWidth;
uniform int u_ScreenHeight;
uniform sampler2D array;

void main()
{    
	double x = gl_FragCoord.x / u_ScreenWidth;
	double y = gl_FragCoord.y / u_ScreenHeight;
    FragColor = texture(array, vec2(x,y));
}