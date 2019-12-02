#version 450 core

// Skybox의 텍스쳐 좌표
in vec3 o_TextureCoords;
// 최종적으로 계산된 Pixel 컬러
out vec4 fragmentColor;

struct Ray {
	vec3 origin;
	vec3 direction;
};

struct Sphere {
	vec3 position;
	float radius;
};

// 충돌시의 결과
struct Intersect {
	// 법선벡터
	vec3 normal;
	// 충돌 점
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
// 카메라의 좌표
uniform int u_ScreenWidthHalf;
uniform int u_ScreenHeightHalf;
uniform float u_Distance;
// Skybox 텍스쳐
uniform samplerCube skybox;
uniform mat4 u_View;
// 광원에 대한 구조체를 입력받습니다
uniform Light light;
// Object에 대한 재질 구조체를 입력받습니다
uniform Material material;

// 삼각형과 광선의 충돌시 t를 구합니다 충돌하지 않으면 최대 거리를 리턴합니다
Intersect IntersectTriangle(Ray r, vec3 v0, vec3 v1, vec3 v2) {
	Intersect inter;
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0;
	vec3 N = cross(v0v1, v0v2);
    float area2 = N.length(); 
 
    // 광선과 삼각형이 평행한지 계산합니다
	float NdotRayDirection = dot(N, r.direction);
    if (NdotRayDirection < 0.0000001f && NdotRayDirection > -0.0000001f) {
		inter.t = 1000;
        return inter;
	}

	float d = dot(N, v0);
    // t를 계산합니다
	float t = (dot(N, r.origin) + d) / NdotRayDirection;
    // 삼각형이 광선 반대에 있는지 확인합니다
    if (t < 0) {
		inter.t = 1000;
        return inter;
	}
	// 교차점을 계산합니다
    vec3 P = r.origin + t * r.direction; 
 
    // 교차점이 삼각형 내부에 있는지 확인합니다
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
	// 광선을 Pixel을 향해 쏩니다
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

	// 광선의 최대 거리를 설정합니다
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
		// 1번 큐브를 계산합니다 하늘색
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

		// 2번 큐브를 계산합니다 연두색
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

		// 하늘색이 더 가깝습니다
		if (t1.t < t2.t){
			// 광원에서의 입사벡터를 구한다
			lightDir = normalize(light.position - t1.point);
			// diffuse 상수를 구한다
			diff = max(dot(lightDir, t1.normal), 0.0);
			ambient = vec4(0.2431f, 0.7725f, 0.9451f, 1.0f) * 0.15;
			diffuse = vec4(light.diffuse * diff * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f);
			// 광원에서의 입사벡터의 반사벡터를 구한다
			lightReflection = normalize(reflect(-lightDir, t1.normal));
			// specular 상수를 구한다
			spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 10);

			// 색을 계산합니다
			if (j == 0){
				result = ambient + diffuse + spec;
			}
			else {
				result += (ambient + diffuse + spec) * 0.5f;
			}

			// 광선의 반사벡터를 구한다
			ray.origin = t1.point;
			// ray.direction = normalize(reflect(ray.direction, t1.normal));
			ray.direction = lightDir;
		}
		else if (t1.t > t2.t) {
			// 광원에서의 입사벡터를 구한다
			lightDir = normalize(light.position - t2.point);
			// diffuse 상수를 구한다
			diff = max(dot(lightDir, t2.normal), 0.0);
			ambient = vec4(0.6392f, 0.8235f, 0.4706f, 1.0f) * 0.15;
			diffuse = vec4(light.diffuse * diff * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f);
			// 광원에서의 입사벡터의 반사벡터를 구한다
			lightReflection = normalize(reflect(-lightDir, t2.normal));
			// specular 상수를 구한다
			spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 10);

			// 색을 계산합니다
			if (j == 0){
				result = ambient + diffuse + spec;
			}
			else {
				result += (ambient + diffuse + spec) * 0.5f;
			}

			// 광선의 반사벡터를 구한다
			ray.origin = t2.point;
			// ray.direction = normalize(reflect(ray.direction, t2.normal));
			ray.direction = lightDir;
		}
		else {
			// 색을 계산합니다
			if (j == 0){
				result = texture(skybox, o_TextureCoords);
			}
			else {
				// 광선의 반사벡터를 구한다
				rayReflection = normalize(vec3(inverse(u_View) * vec4(ray.direction, 1)));
				result += texture(skybox, rayReflection) * 0.5f;
			}
		}
	}
	fragmentColor = result;
}