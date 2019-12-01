#version 450 core

// Skybox�� �ؽ��� ��ǥ
in vec3 o_TextureCoords;
// ���������� ���� Pixel �÷�
out vec4 fragmentColor;

struct Ray {
	vec3 origin;
	vec3 direction;
};

struct Sphere {
	vec3 position;
	float radius;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    float shininess;
}; 

// Vertex Array
uniform int arr_size;
uniform vec3 arr[];
// ī�޶��� ��ǥ
uniform int u_ScreenWidthHalf;
uniform int u_ScreenHeightHalf;
uniform float u_Distance;
// Skybox �ؽ���
uniform samplerCube skybox;
uniform mat4 u_View;
// ������ ���� ����ü�� �Է¹޽��ϴ�
uniform Light light;
// Object�� ���� ���� ����ü�� �Է¹޽��ϴ�
uniform Material material;

// �ﰢ���� ������ �浹�� t�� ���մϴ� �浹���� ������ �ִ� �Ÿ��� �����մϴ�
float IntersectTriangle(Ray r, vec3 v1, vec3 v2, vec3 v3) {
	vec3 edge1 = v2 - v1;
    vec3 edge2 = v3 - v1;
    vec3 h = cross(r.direction, edge2);
    float a = dot(h, edge2);
    if(a > -0.00001 && a < 0.00001){
        return 1000;
	}
    float f = 1 / a;
    vec3 s = r.origin - v1;
    float u = f * dot(s, h);
    if(u < 0.0f || u > 1.0f){
        return 1000;
	}
    vec3 q = cross(s, edge1);
    float v = f * dot(r.direction, q);
    if(v < 0 || u + v > 1){
        return 1000;
	}
    return dot(edge2, q);
}

float IntersectSphere(Ray r, Sphere s) {
	return 0.0f;
}

void main()
{
	// ������ Pixel�� ���� ���ϴ�
	Ray ray;
	ray.origin = vec3(0, 0, 0);
	float x = gl_FragCoord.x - u_ScreenWidthHalf;
	float y = gl_FragCoord.y - u_ScreenHeightHalf;
	ray.direction = normalize(vec3(x, y, -u_Distance));

	vec4 result = vec4(0.0f);
	vec4 ambient = vec4(0.0f);
	vec4 diffuse = vec4(0.0f);
	vec4 specular = vec4(0.0f);

	Sphere sphere;
	sphere.position = arr[72];
	sphere.radius = 2.0f;
	vec3 l = sphere.position - ray.origin;
	float s = dot(l, ray.direction);
	float l2 = dot(l,l);
	float r2 = pow(sphere.radius, 2);
	float m2 = l2 - pow(s,2);
	/*
		if�� : ������ �浹�ϴ��� ����մϴ�
		else if�� : ī�޶� �� �ȿ� �ִ��� ����մϴ�
		else�� : ������ ���� �浹�ϰ� ī�޶� �� �ۿ� �ֽ��ϴ�
	*/
	if (s < 0) {
		result = texture(skybox, o_TextureCoords);
	} else if (m2 > r2) {
		result = texture(skybox, o_TextureCoords);
	} else {
		float q = sqrt(r2 - m2);
		float dist = 0;
		// �� ���� ������ �� ������� ���ϴ°�?   
		if( l2 > r2 ) {
			dist = s - q;
		} else {
			dist = s + q;
		}
		// �������� ����Ѵ�
		vec3 intersection = ray.origin + dist * ray.direction;
		// �������� �������͸� ���Ѵ�
		vec3 normal = normalize(intersection - sphere.position);
		// ���������� �Ի纤�͸� ���Ѵ�
		vec3 lightDir = normalize(light.position - intersection);
		// ������ �ݻ纤�͸� ���Ѵ�
		vec3 rayReflection = normalize(vec3(inverse(u_View) * vec4(reflect(ray.direction, normal),1)));
		vec3 viewDir = normalize(vec3(0,0,0) - intersection);
		// ���������� �Ի纤���� �ݻ纤�͸� ���Ѵ�
		vec3 lightReflection = normalize(reflect(-lightDir, normal));
		// diffuse ����� ���Ѵ�
		float diff = max(dot(lightDir, normal), 0.0);
		// specular ����� ���Ѵ�
		float spec = pow(max(dot(viewDir, lightReflection), 0.0f), 30);

		diffuse = vec4(light.diffuse * diff * material.diffuse, 1.0f);
		specular = vec4(light.specular * spec * material.specular, 1.0f);
		result += diffuse + specular;
	}
   fragmentColor = result;
}