#version 450 core

layout(location = 0) in vec3 vertexPosition; // Each Vertex's Position
layout(location = 1) in vec2 vertexUV; // Each Vertex has texture's Coordinates
layout(location = 2) in vec3 vertexNormal; // Each Vertex has their NormalVector

out vec2 textureCoord; // put vertexUV on FragmentShader
out vec3 normalVector; // put NormalVector on FramentShader

uniform mat4 model; // Object's local system -> world system
uniform mat4 view; // Camera's local system -> world system
uniform mat4 projection; // Project world system to Camera

void main()
{
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	textureCoord = vertexUV;
	normalVector = mat3(transpose(inverse(model))) * vertexNormal; 
}