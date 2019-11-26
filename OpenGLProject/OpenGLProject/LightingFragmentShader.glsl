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
	vec4 texColor = texture(textureSampler, textureCoord); // �ؽ����� ���� ����ϴ�
	// �ؽ����� ������ �κ��� ���ܽ�ŵ�ϴ�
    if(texColor.a == 0) {
        discard;
	}

	// ambient
    vec3 ambient = light.ambient * material.ambient;

	// diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
<<<<<<< Updated upstream
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
	vec4 textureColor = defaultColor + texture(textureSampler, textureCoord);
	fragmentColor = vec4(ambient, 1.0) * textureColor;
=======
    vec3 viewDir = normalize(u_CameraPosition - o_VertexPosition); // �������� Camera���� Vector�� ���մϴ�
    vec3 reflectDir = reflect(-lightDir, norm); // �������� �ݻ�� Vector�� ���մϴ�
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1); // �Ի簢�� ����ϰ� shininess�� �����ŵ�ϴ�
    vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	// defaultColor�� 0,0,0�̸� texture�� ����ǰ� 1,1,1�̸� ������� �ʽ��ϴ�
	vec4 textureColor = defaultColor + texColor;
	fragmentColor = vec4(result, 1.0) * textureColor;
>>>>>>> Stashed changes
}