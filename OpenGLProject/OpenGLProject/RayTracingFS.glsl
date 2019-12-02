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

// �浹���� ���
struct Intersect {
	// ��������
	vec3 normal;
	// �浹 ��
	vec3 point;
	float t;
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
uniform float arr[219];
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
Intersect IntersectTriangle(Ray r, vec3 v0, vec3 v1, vec3 v2) {
	Intersect inter;
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0;
	vec3 N = cross(v0v1, v0v2);
    float area2 = N.length(); 
 
    // ������ �ﰢ���� �������� ����մϴ�
	float NdotRayDirection = dot(N, r.direction);
    if (NdotRayDirection < 0.0000001f && NdotRayDirection > -0.0000001f) {
		inter.t = 1000;
        return inter;
	}

	float d = dot(N, v0);
    // t�� ����մϴ�
	float t = (dot(N, r.origin) + d) / NdotRayDirection;
    // �ﰢ���� ���� �ݴ뿡 �ִ��� Ȯ���մϴ�
    if (t < 0) {
		inter.t = 1000;
        return inter;
	}
	// �������� ����մϴ�
    vec3 P = r.origin + t * r.direction; 
 
    // �������� �ﰢ�� ���ο� �ִ��� Ȯ���մϴ�
    vec3 C; // vector perpendicular to triangle's plane 
 
    // edge 0
    vec3 edge = v1 - v0;
    vec3 vp = P - v0;
	C = cross(edge, vp);
	if (dot(N, C) < 0) {
		inter.t = 1000;
        return inter;
	}

    // edge 1
    edge = v2 - v1;
    vp = P - v1;
	C = cross(edge, vp);
    if (dot(N, C) < 0) {
		inter.t = 1000;
        return inter;
	}

    // edge 2
    edge = v0 - v2;
    vp = P - v2;
    C = cross(edge, vp);
    if (dot(N, C) < 0) {
		inter.t = 1000;
        return inter;
	}

	inter.normal = -normalize(N);
	inter.point = r.origin + t * r.direction;
	inter.t = t;
	return inter;
} 

void main()
{
	// ������ Pixel�� ���� ���ϴ�
	Ray ray;
	ray.origin = vec3(0, 0, 0);
	float x = gl_FragCoord.x - u_ScreenWidthHalf;
	float y = gl_FragCoord.y - u_ScreenHeightHalf;
	ray.direction = normalize(vec3(x, y, -u_Distance));
	Sphere sphere;
	// sphere.position = arr[72];
	sphere.radius = 2.0f;

	vec4 result = vec4(0.0f);
	vec4 ambient;
	vec4 diffuse = vec4(0.0f);
	vec4 specular = vec4(0.0f);
	float diff, spec;
	vec3 lightDir, lightReflection, rayReflection;

	// ������ �ִ� �Ÿ��� �����մϴ�
	Intersect t1;
	t1.t = 1000;
	vec3 n1;
	
	Intersect t2;
	t2.t = 1000;
	vec3 n2;

	int tracingCount = 2;
	vec3 a, b, c;
	Intersect tmp;
	for(int j = 0; j < tracingCount; j++) {
		t1.t = 1000;
		t2.t = 1000;
		// 1�� ť�긦 ����մϴ� �ϴû�
		for (int i = 0; i < 12; i++) {
			a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
			b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
			c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
			tmp = IntersectTriangle(ray, a, b, c);
			if (t1.t > tmp.t){
				t1.t = tmp.t;
				t1.point = tmp.point;
				t1.normal = tmp.normal;
			}
		}

		// 2�� ť�긦 ����մϴ� ���λ�
		for (int i = 12; i < 24; i++) {
			a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
			b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
			c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
			tmp = IntersectTriangle(ray, a, b, c);
			if (t2.t > tmp.t){
				t2.t = tmp.t;
				t2.point = tmp.point;
				t2.normal = tmp.normal;
			}
		}

		// �ϴû��� �� �������ϴ�
		if (t1.t < t2.t){
			// ���������� �Ի纤�͸� ���Ѵ�
			lightDir = normalize(light.position - t1.point);
			// diffuse ����� ���Ѵ�
			diff = max(dot(lightDir, t1.normal), 0.0);
			ambient = vec4(0.2431f, 0.7725f, 0.9451f, 1.0f) * 0.15;
			diffuse = vec4(light.diffuse * diff * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f);
			// ���������� �Ի纤���� �ݻ纤�͸� ���Ѵ�
			lightReflection = normalize(reflect(-lightDir, t1.normal));
			// specular ����� ���Ѵ�
			spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 10);

			// ���� ����մϴ�
			if (j == 0){
				result = ambient + diffuse + spec;
			}
			else {
				result += (ambient + diffuse + spec) * 0.5f;
			}

			// ������ �ݻ纤�͸� ���Ѵ�
			ray.origin = t1.point;
			// ray.direction = normalize(reflect(ray.direction, t1.normal));
			ray.direction = lightDir;
		}
		else if (t1.t > t2.t) {
			// ���������� �Ի纤�͸� ���Ѵ�
			lightDir = normalize(light.position - t2.point);
			// diffuse ����� ���Ѵ�
			diff = max(dot(lightDir, t2.normal), 0.0);
			ambient = vec4(0.6392f, 0.8235f, 0.4706f, 1.0f) * 0.15;
			diffuse = vec4(light.diffuse * diff * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f);
			// ���������� �Ի纤���� �ݻ纤�͸� ���Ѵ�
			lightReflection = normalize(reflect(-lightDir, t2.normal));
			// specular ����� ���Ѵ�
			spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 10);

			// ���� ����մϴ�
			if (j == 0){
				result = ambient + diffuse + spec;
			}
			else {
				result += (ambient + diffuse + spec) * 0.5f;
			}

			// ������ �ݻ纤�͸� ���Ѵ�
			ray.origin = t2.point;
			// ray.direction = normalize(reflect(ray.direction, t2.normal));
			ray.direction = lightDir;
		}
		else {
			// ���� ����մϴ�
			if (j == 0){
				result = texture(skybox, o_TextureCoords);
			}
			else {
				// ������ �ݻ纤�͸� ���Ѵ�
				rayReflection = normalize(vec3(inverse(u_View) * vec4(ray.direction, 1)));
				result += texture(skybox, rayReflection) * 0.5f;
			}
		}
	}
	fragmentColor = result;
}