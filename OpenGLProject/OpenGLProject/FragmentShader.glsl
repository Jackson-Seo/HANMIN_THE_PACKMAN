#version 450 core

in vec2 textureCoord; // Texture ÁÂÇ¥
out vec4 fragmentColor;

uniform sampler2D textureSampler; // Texture °´Ã¼

void main()
{
	fragmentColor = texture( textureSampler, textureCoord ).rgba * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}