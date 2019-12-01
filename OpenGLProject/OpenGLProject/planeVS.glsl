#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model; // �� Object�� local ��ǥ�� world ��ǥ�� ��ȯ�մϴ�
uniform mat4 view; // ī�޶��� local ��ǥ�� world ��ǥ�� ��ȯ�մϴ�
uniform mat4 projection; // world�� ī�޶� ������ŵ�ϴ�

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}