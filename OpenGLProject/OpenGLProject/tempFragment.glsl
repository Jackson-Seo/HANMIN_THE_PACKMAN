#version 450 core

in vec2 textureCoord; // Each Vertex has texture's Coordinates
in vec3 normalVector; // Each Vertex has their NormalVector
in vec3 o_VertexPosition; // world������ Vertex ��ǥ
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

uniform vec3 u_CameraPosition; // ī�޶��� ��ǥ
uniform vec4 defaultColor; // Use this when Object doesn't have Texture
uniform sampler2D textureSampler; // Neccesary Texture data
uniform Material material; // �׸� Object�� ���� ���� ����ü�� �Է¹޽��ϴ�
uniform Light light; // ������ ���� ����ü�� �Է¹޽��ϴ�

void main()
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;

	// diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(light.position - o_VertexPosition); // ������ �Ի��ϴ� Vector�� ���մϴ�
    float diff = max(dot(norm, lightDir), 0.0); // �Ի簢�� ����մϴ�
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
   
    // specular
    vec3 viewDir = normalize(u_CameraPosition - o_VertexPosition); // �������� Camera���� Vector�� ���մϴ�
    vec3 reflectDir = reflect(-lightDir, norm); // �������� �ݻ�� Vector�� ���մϴ�
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // �Ի簢�� ����ϰ� shininess�� �����ŵ�ϴ�
    vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	// defaultColor�� 0,0,0�̸� texture�� ����ǰ� 1,1,1�̸� ������� �ʽ��ϴ�
	vec4 textureColor = defaultColor + texture(textureSampler, textureCoord);
	fragmentColor = vec4(result, 1.0) * textureColor;
}