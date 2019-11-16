#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
in vec3 normalVector; // Each Vertex has their NormalVector
out vec4 fragmentColor; // Return each Pixel's color

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec4 defaultColor; // Use this when Object doesn't have Texture
uniform sampler2D textureSampler; // Neccesary Texture data
uniform Material material;
uniform Light light;

void main()
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;

	// diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
	vec4 textureColor = defaultColor + texture(textureSampler, textureCoord);
	fragmentColor = vec4(ambient, 1.0) * textureColor;
}