#version 450 core

layout(location = 0) in vec3 vertexPosition; // �� Vertex�� ��ġ�Դϴ�
layout(location = 1) in vec2 vertexUV; // �� Vertex�� �����ִ� Texture ���� ��ǥ�Դϴ�
out vec2 textureCoord; // Texture ���� ��ǥ�� FragmentShader�� �Ѱ��ݴϴ�

uniform mat4 model; // �� Object�� local ��ǥ�� world ��ǥ�� ��ȯ�մϴ�
uniform mat4 view; // ī�޶��� local ��ǥ�� world ��ǥ�� ��ȯ�մϴ�
uniform mat4 projection; // world�� ī�޶� ������ŵ�ϴ�

void main()
{
	// gl_Position�� �������� Vertex�� ��ġ�Դϴ�
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	textureCoord = vertexUV;
}