#version 450 core

layout(location = 0) in vec3 vertexPosition; // Each Vertex's Position

out vec3 o_TextureCoords; // 텍스쳐의 좌표

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    o_TextureCoords = vertexPosition;
    vec4 pos = u_Projection * u_View * vec4(vertexPosition, 1.0);
    gl_Position = pos.xyww; // z값을 항상 1로 설정하게 한다
}  