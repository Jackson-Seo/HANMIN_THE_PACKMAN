#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
in vec3 normalVector; // Each Vertex has their NormalVector
in vec3 o_VertexPosition; // world에서의 Vertex 좌표
out vec4 fragmentColor; // Return each Pixel's color

struct Ray {
	vec3 origin;
	vec3 direction;
};

// 카메라의 좌표
uniform int u_ScreenWidthHalf;
uniform int u_ScreenHeightHalf;
uniform float u_Distance;
uniform vec3 u_CameraPosition;
uniform mat4 u_InverseView;

void main()
{
	Ray ray;
	ray.origin = vec3(u_InverseView * vec4(0, 0, 0, 1));
	float x = gl_FragCoord.x - u_ScreenWidthHalf;
	float y = gl_FragCoord.y - u_ScreenHeightHalf;
	ray.direction = normalize(vec3(u_InverseView * vec4(x, y, -u_Distance, 1)));
}