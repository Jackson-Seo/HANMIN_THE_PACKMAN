#version 450 core

layout(location = 0) in vec3 vertexPosition; // Each Vertex's Position
layout(location = 1) in vec2 vertexUV; // Each Vertex has texture's Coordinates
layout(location = 2) in vec3 vertexNormal; // Each Vertex has their NormalVector

out vec2 textureCoord; // put vertexUV on FragmentShader
out vec3 normalVector; // put NormalVector on FramentShader
out vec3 o_VertexPosition; // world에서의 Vertex 좌표

uniform mat4 model; // Object's local system -> world system
uniform mat4 view; // Camera's local system -> world system
uniform mat4 projection; // Project world system to Camera

void main()
{
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0f); // 최종적으로 화면에 출력될 Vertex Position을 계산합니다
	textureCoord = vertexUV; // Texture의 좌표를 FragmentShader로 넘깁니다
	normalVector = mat3(transpose(inverse(model))) * vertexNormal; // world에서의 Normal Vector를 계산하고 FragmentShader로 넘깁니다
	o_VertexPosition = vec3(model * vec4(vertexPosition, 1.0)); // world에서의 Vertex 좌표를 계산하고 FragmentShader로 넘깁니다