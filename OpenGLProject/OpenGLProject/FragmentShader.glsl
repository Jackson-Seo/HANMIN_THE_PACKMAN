#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
out vec4 fragmentColor; // Return each Pixel's color

uniform sampler2D textureSampler; // Neccesary Texture data
uniform vec4 defaultColor; // Use this when Object doesn't have Texture

void main()
{
	fragmentColor = texture( textureSampler, textureCoord ) + defaultColor;
}