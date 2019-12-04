#version 450 core

// Skybox�� �ؽ��� ��ǥ
in vec3 o_TextureCoords;
// ���������� ���� Pixel �÷�
out vec4 fragmentColor;

struct Ray {
	vec3 origin;
	vec3 direction;
	vec3 direction2;
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
	// �浹 ���� ����
	bool hit;
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
	inter.hit = false;
	inter.t = 1000;
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0;
	vec3 N = -cross(v0v1, v0v2);
    float area2 = N.length(); 
 
    // ������ �ﰢ���� �������� ����մϴ�
	float NdotRayDirection = dot(N, r.direction);
    if (NdotRayDirection > -0.0000001f) {
		inter.t = 1000;
        return inter;
	}

	float d = dot(N, v0);
    // t�� ����մϴ�
	float t = (dot(N, r.origin) + d) / NdotRayDirection;
    // �ﰢ���� ���� �ݴ뿡 �ִ��� Ȯ���մϴ�
    if (t < 0) {
        return inter;
	}
	// �������� ����մϴ�
    vec3 P = r.origin + t * r.direction; 
 
    // �������� �ﰢ�� ���ο� �ִ��� Ȯ���մϴ�
    vec3 C; // vector perpendicular to triangle's plane 
 
    // edge 0
    vec3 edge = v1 - v0;
    vec3 vp = P - v0;
	C = -cross(edge, vp);
	if (dot(N, C) < 0) {
        return inter;
	}

    // edge 1
    edge = v2 - v1;
    vp = P - v1;
	C = -cross(edge, vp);
    if (dot(N, C) < 0) {
        return inter;
	}

    // edge 2
    edge = v0 - v2;
    vp = P - v2;
    C = -cross(edge, vp);
    if (dot(N, C) < 0) {
        return inter;
	}

	inter.normal = normalize(N);
	inter.point = r.origin + t * r.direction;
	inter.t = t;
	inter.hit = true;
	return inter;
} 

Intersect IntersectSphere(Ray r, Sphere sp) {
	Intersect inter;
	inter.hit = false;
	vec3 l = sp.position - r.origin;
	float s = dot(l, r.direction);
	float l2 = dot(l,l);
	float r2 = pow(sp.radius, 2);
	float m2 = l2 - pow(s,2);
	/*
		if�� : ������ �浹�ϴ��� ����մϴ�
		else if�� : ī�޶� �� �ȿ� �ִ��� ����մϴ�
		else�� : ������ ���� �浹�ϰ� ī�޶� �� �ۿ� �ֽ��ϴ�
	*/
	if (s < 0) {
		inter.t = 1000;
	} else if (m2 > r2) {
		inter.t = 1000;
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
		inter.point = r.origin + dist * r.direction;
		// �������� �������͸� ���Ѵ�
		inter.normal = normalize(inter.point - sp.position);
		inter.t = dist;
		inter.hit = true;
	}
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
	sphere.position = vec3(arr[216], arr[217], arr[218]);
	sphere.radius = 3.0f;

	vec4 result = vec4(0.0f);
	vec4 ambient;
	vec4 diffuse = vec4(0.0f);
	vec4 specular = vec4(0.0f);
	float diff, spec;
	vec3 lightDir, lightReflection, rayReflection, normal;

	// ������ �ִ� �Ÿ��� �����մϴ�
	Intersect t1;
	t1.t = 1000;
	vec3 n1;
	
	Intersect t2;
	t2.t = 1000;
	vec3 n2;

	Intersect t3;
	t3.t = 1000;
	vec3 n3;

	// �ݻ� Ƚ���Դϴ�
	int tracingCount = 6;
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
				t1 = tmp;
			}
		}

		// 2�� ť�긦 ����մϴ� ���λ�
		for (int i = 12; i < 24; i++) {
			a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
			b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
			c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
			tmp = IntersectTriangle(ray, a, b, c);
			if (t2.t > tmp.t){
				t2 = tmp;
			}
		}

		// ������ �浹�� ����մϴ� ������
		t3 = IntersectSphere(ray, sphere);

		if (t1.t < t2.t){
			// �ϴû� ť�갡 �� �������ϴ�
			if (t1.t < t3.t) {
				normal = t1.normal;
				// ���������� �Ի纤�͸� ���Ѵ�
				lightDir = normalize(light.position - t1.point);
				ambient = vec4(0.2431f, 0.7725f, 0.9451f, 1.0f) * 0.3f;
				// diffuse ����� ���Ѵ�
				diff = max(dot(lightDir, t1.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f) * 0.5f;
				// ���������� �Ի纤���� �ݻ纤�͸� ���Ѵ�
				lightReflection = normalize(reflect(-lightDir, t1.normal));
				// specular ����� ���Ѵ�
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f) * 0.5f;

				// ���������� ������ �߻��մϴ�
				ray.origin = t1.point;
				ray.direction2 = normalize(reflect(ray.direction, t1.normal));
				ray.direction = lightDir;
			}
			// ���� �� �������ϴ�
			else {
				normal = t3.normal;
				lightDir = normalize(light.position - t3.point);
				ambient = vec4(0.8627f, 0.0784f, 0.2353f, 1.0f) * 0.3f;
				diff = max(dot(lightDir, t3.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;
				lightReflection = normalize(reflect(-lightDir, t3.normal));
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;

				ray.origin = t3.point;
				ray.direction2 = normalize(reflect(ray.direction, t3.normal));
				ray.direction = lightDir;
			}
		}
		else if (t1.t > t2.t) {
			// �ʷϻ� ť�갡 �� �������ϴ�
			if (t2.t < t3.t) {
				normal = t2.normal;
				// ���������� �Ի纤�͸� ���Ѵ�
				lightDir = normalize(light.position - t2.point);
				// diffuse ����� ���Ѵ�
				ambient = vec4(0.6392f, 0.8235f, 0.4706f, 1.0f) * 0.3f;
				diff = max(dot(lightDir, t2.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f) * 0.5f;
				// ���������� �Ի纤���� �ݻ纤�͸� ���Ѵ�
				lightReflection = normalize(reflect(-lightDir, t2.normal));
				// specular ����� ���Ѵ�
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f) * 0.5f;

				// ���������� ������ �߻��մϴ�
				ray.origin = t2.point;
				ray.direction2 = normalize(reflect(ray.direction, t2.normal));
				ray.direction = lightDir;
			}
			// ���� �� �������ϴ�
			else {
				normal = t3.normal;
				lightDir = normalize(light.position - t3.point);
				ambient = vec4(0.8627f, 0.0784f, 0.2353f, 1.0f) * 0.3f;
				diff = max(dot(lightDir, t3.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;
				lightReflection = normalize(reflect(-lightDir, t3.normal));
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;

				ray.origin = t3.point;
				ray.direction2 = normalize(reflect(ray.direction, t3.normal));
				ray.direction = lightDir;
			}
		}
		// ���� ����ϴ�
		else if (t3.hit == true) {
			normal = t3.normal;
			lightDir = normalize(light.position - t3.point);
			ambient = vec4(0.8627f, 0.0784f, 0.2353f, 1.0f) * 0.3f;
			diff = max(dot(lightDir, t3.normal), 0.0);
			diffuse = vec4(light.diffuse * diff * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;
			lightReflection = normalize(reflect(-lightDir, t3.normal));
			spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
			specular = vec4(light.specular * spec * vec3(0.8627f, 0.0784f, 0.2353f), 1.0f) * 0.5f;

			ray.origin = t3.point;
			ray.direction2 = normalize(reflect(ray.direction, t3.normal));
			ray.direction = lightDir;
		}
		else {
			if (j == 0) {
				result = texture(skybox, o_TextureCoords);
			}
			else {
				rayReflection = normalize(vec3(inverse(u_View) * vec4(ray.direction, 1)));
				result += texture(skybox, rayReflection) * 0.2f;
			}
			break;
		}

		if (dot(ray.direction, normal) < 0) {
			ray.direction = ray.direction2;
			result += ambient;
		}
		else {
			t1.t = 1000;
			t2.t = 1000;

			// 1�� ť�긦 ����մϴ� �ϴû�
			for (int i = 0; i < 12; i++) {
				a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
				b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
				c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
				tmp = IntersectTriangle(ray, a, b, c);
				if (t1.t > tmp.t){
					t1 = tmp;
				}
			}

			// 2�� ť�긦 ����մϴ� ���λ�
			for (int i = 12; i < 24; i++) {
				a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
				b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
				c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
				tmp = IntersectTriangle(ray, a, b, c);
				if (t2.t > tmp.t){
					t2 = tmp;
				}
			}

			t3 = IntersectSphere(ray, sphere);

			if (t1.t == 1000 && t2.t == 1000 && t3.t == 1000) {
				rayReflection = normalize(vec3(inverse(u_View) * vec4(ray.direction2, 0)));
				result += texture(skybox, rayReflection) * 0.2f;
				result += ambient + diffuse + specular;
				// ������ �ݻ纤�͸� ���Ѵ�
				break;
			}
			else {
				result += ambient ;
				ray.direction = ray.direction2;
			}
		}
	}
	fragmentColor = result;
}