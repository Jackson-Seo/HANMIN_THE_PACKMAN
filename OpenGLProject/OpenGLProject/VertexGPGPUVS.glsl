#version 450 core

layout(location = 0) in vec3 vertexPosition; // Each Vertex's Position

void main()
{
    vec4 pos = vec4(vertexPosition, 1.0);
    gl_Position = pos.xyww; // z값을 항상 1로 설정하게 한다
}  