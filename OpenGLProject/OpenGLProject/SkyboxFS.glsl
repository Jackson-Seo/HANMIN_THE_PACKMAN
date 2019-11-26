#version 450 core

out vec4 FragColor;

in vec3 o_TextureCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, o_TextureCoords);
}