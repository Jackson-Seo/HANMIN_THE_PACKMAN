#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
out vec4 fragmentColor; // Return each Pixel's color

uniform vec4 defaultColor; // Use this when Object doesn't have Texture
uniform sampler2D textureSampler; // Neccesary Texture data


void main()
{
	fragmentColor = defaultColor + texture(textureSampler, textureCoord);
}