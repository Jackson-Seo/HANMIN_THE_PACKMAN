#version 450 core

layout(location = 0) in vec3 vertexPosition; // 각 Vertex의 위치입니다
layout(location = 1) in vec2 vertexUV; // 각 Vertex가 갖고있는 Texture 매핑 좌표입니다
out vec2 textureCoord; // Texture 매핑 좌표를 FragmentShader로 넘겨줍니다

uniform mat4 model; // 각 Object의 local 좌표를 world 좌표로 변환합니다
uniform mat4 view; // 카메라의 local 좌표를 world 좌표로 변환합니다
uniform mat4 projection; // world를 카메라에 투영시킵니다

void main()
{
	// gl_Position이 최종적인 Vertex의 위치입니다
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	textureCoord = vertexUV;
}