#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
out vec4 fragmentColor; // Return each Pixel's color

uniform sampler2D textureSampler; // Neccesary Texture data

void main()
{
	fragmentColor = texture( textureSampler, textureCoord ).rgba * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}