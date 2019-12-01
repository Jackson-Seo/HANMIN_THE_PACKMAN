#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model; // 각 Object의 local 좌표를 world 좌표로 변환합니다
uniform mat4 view; // 카메라의 local 좌표를 world 좌표로 변환합니다
uniform mat4 projection; // world를 카메라에 투영시킵니다

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}