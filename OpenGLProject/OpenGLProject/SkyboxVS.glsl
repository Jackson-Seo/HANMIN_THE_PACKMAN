#version 450 core

layout(location = 0) in vec3 vertexPosition; // Each Vertex's Position

out vec3 o_TextureCoords; // �ؽ����� ��ǥ

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    o_TextureCoords = vertexPosition;
    vec4 pos = u_Projection * u_View * vec4(vertexPosition, 1.0);
    gl_Position = pos.xyww; // z���� �׻� 1�� �����ϰ� �Ѵ�
}  