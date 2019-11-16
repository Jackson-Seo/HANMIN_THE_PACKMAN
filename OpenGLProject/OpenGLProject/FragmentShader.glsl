#version 450 core

in vec2 textureCoord; // Texture ��ǥ
out vec4 fragmentColor;

uniform sampler2D textureSampler; // Texture ��ü

void main()
{
	fragmentColor = texture( textureSampler, textureCoord ).rgba * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}