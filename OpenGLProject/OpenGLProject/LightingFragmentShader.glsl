#version 450 core

in vec2 textureCoord; // Texture ÁÂÇ¥
out vec4 fragmentColor;

uniform vec4 defaultColor;
uniform sampler2D textureSampler; // Texture °´Ã¼

void main()
{
	fragmentColor = defaultColor + texture( textureSampler, textureCoord).rgba;
}