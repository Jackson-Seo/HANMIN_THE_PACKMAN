#version 450 core

in vec2 textureCoord; // Texture ��ǥ
out vec4 fragmentColor;

uniform vec4 defaultColor;
uniform sampler2D textureSampler; // Texture ��ü

void main()
{
	fragmentColor = defaultColor + texture( textureSampler, textureCoord).rgba;
}