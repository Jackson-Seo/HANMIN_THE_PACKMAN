#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
in vec3 normalVector; // Each Vertex has their NormalVector
in vec3 o_VertexPosition; // world에서의 Vertex 좌표
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

uniform vec3 u_CameraPosition; // 카메라의 좌표
uniform vec4 defaultColor; // Use this when Object doesn't have Texture
uniform sampler2D textureSampler; // Neccesary Texture data
uniform Material material; // 그릴 Object에 대한 재질 구조체를 입력받습니다
uniform Light light; // 광원에 대한 구조체를 입력받습니다

void main()
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;

	// diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(light.position - o_VertexPosition); // 정점에 입사하는 Vector를 구합니다
    float diff = max(dot(norm, lightDir), 0.0); // 입사각을 계산합니다
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
   
    // specular
    vec3 viewDir = normalize(u_CameraPosition - o_VertexPosition); // 정점에서 Camera로의 Vector를 구합니다
    vec3 reflectDir = reflect(-lightDir, norm); // 정점에서 반사된 Vector를 구합니다
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 입사각을 계산하고 shininess를 적용시킵니다
    vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	// defaultColor가 0,0,0이면 texture가 적용되고 1,1,1이면 적용되지 않습니다
	vec4 textureColor = defaultColor + texture(textureSampler, textureCoord);
	fragmentColor = vec4(result, 1.0) * textureColor;
}