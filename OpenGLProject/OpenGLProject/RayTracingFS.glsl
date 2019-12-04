#version 450 core

// Skybox의 텍스쳐 좌표
in vec3 o_TextureCoords;
// 최종적으로 계산된 Pixel 컬러
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

// 충돌시의 결과
struct Intersect {
	// 법선벡터
	vec3 normal;
	// 충돌 점
	vec3 point;
	float t;
	// 충돌 성공 여부
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
	inter.hit = false;
	inter.t = 1000;
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0;
	vec3 N = -cross(v0v1, v0v2);
    float area2 = N.length(); 
 
    // 광선과 삼각형이 평행한지 계산합니다
	float NdotRayDirection = dot(N, r.direction);
    if (NdotRayDirection > -0.0000001f) {
		inter.t = 1000;
        return inter;
	}

	float d = dot(N, v0);
    // t를 계산합니다
	float t = (dot(N, r.origin) + d) / NdotRayDirection;
    // 삼각형이 광선 반대에 있는지 확인합니다
    if (t < 0) {
        return inter;
	}
	// 교차점을 계산합니다
    vec3 P = r.origin + t * r.direction; 
 
    // 교차점이 삼각형 내부에 있는지 확인합니다
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
		if문 : 광선이 충돌하는지 계산합니다
		else if문 : 카메라가 구 안에 있는지 계산합니다
		else문 : 광선이 구와 충돌하고 카메라가 구 밖에 있습니다
	*/
	if (s < 0) {
		inter.t = 1000;
	} else if (m2 > r2) {
		inter.t = 1000;
	} else {
		float q = sqrt(r2 - m2);
		float dist = 0;
		// 두 개의 교차점 중 어느것을 구하는가?   
		if( l2 > r2 ) {
			dist = s - q;
		} else {
			dist = s + q;
		}
		// 교차점을 계산한다
		inter.point = r.origin + dist * r.direction;
		// 교차점의 법선벡터를 구한다
		inter.normal = normalize(inter.point - sp.position);
		inter.t = dist;
		inter.hit = true;
	}
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
	sphere.position = vec3(arr[216], arr[217], arr[218]);
	sphere.radius = 3.0f;

	vec4 result = vec4(0.0f);
	vec4 ambient;
	vec4 diffuse = vec4(0.0f);
	vec4 specular = vec4(0.0f);
	float diff, spec;
	vec3 lightDir, lightReflection, rayReflection, normal;

	// 광선의 최대 거리를 설정합니다
	Intersect t1;
	t1.t = 1000;
	vec3 n1;
	
	Intersect t2;
	t2.t = 1000;
	vec3 n2;

	Intersect t3;
	t3.t = 1000;
	vec3 n3;

	// 반사 횟수입니다
	int tracingCount = 6;
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
				t1 = tmp;
			}
		}

		// 2번 큐브를 계산합니다 연두색
		for (int i = 12; i < 24; i++) {
			a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
			b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
			c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
			tmp = IntersectTriangle(ray, a, b, c);
			if (t2.t > tmp.t){
				t2 = tmp;
			}
		}

		// 구와의 충돌을 계산합니다 빨간색
		t3 = IntersectSphere(ray, sphere);

		if (t1.t < t2.t){
			// 하늘색 큐브가 더 가깝습니다
			if (t1.t < t3.t) {
				normal = t1.normal;
				// 광원에서의 입사벡터를 구한다
				lightDir = normalize(light.position - t1.point);
				ambient = vec4(0.2431f, 0.7725f, 0.9451f, 1.0f) * 0.3f;
				// diffuse 상수를 구한다
				diff = max(dot(lightDir, t1.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f) * 0.5f;
				// 광원에서의 입사벡터의 반사벡터를 구한다
				lightReflection = normalize(reflect(-lightDir, t1.normal));
				// specular 상수를 구한다
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.2431f, 0.7725f, 0.9451f), 1.0f) * 0.5f;

				// 광원쪽으로 광선을 발사합니다
				ray.origin = t1.point;
				ray.direction2 = normalize(reflect(ray.direction, t1.normal));
				ray.direction = lightDir;
			}
			// 구가 더 가깝습니다
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
			// 초록색 큐브가 더 가깝습니다
			if (t2.t < t3.t) {
				normal = t2.normal;
				// 광원에서의 입사벡터를 구한다
				lightDir = normalize(light.position - t2.point);
				// diffuse 상수를 구한다
				ambient = vec4(0.6392f, 0.8235f, 0.4706f, 1.0f) * 0.3f;
				diff = max(dot(lightDir, t2.normal), 0.0);
				diffuse = vec4(light.diffuse * diff * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f) * 0.5f;
				// 광원에서의 입사벡터의 반사벡터를 구한다
				lightReflection = normalize(reflect(-lightDir, t2.normal));
				// specular 상수를 구한다
				spec = pow(max(dot(-ray.direction, lightReflection), 0.0f), 100);
				specular = vec4(light.specular * spec * vec3(0.6392f, 0.8235f, 0.4706f), 1.0f) * 0.5f;

				// 광원쪽으로 광선을 발사합니다
				ray.origin = t2.point;
				ray.direction2 = normalize(reflect(ray.direction, t2.normal));
				ray.direction = lightDir;
			}
			// 구가 더 가깝습니다
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
		// 구에 비춥니다
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

			// 1번 큐브를 계산합니다 하늘색
			for (int i = 0; i < 12; i++) {
				a = vec3(arr[i * 9 + 0], arr[i * 9 + 1], arr[i * 9 + 2]);
				b = vec3(arr[i * 9 + 3], arr[i * 9 + 4], arr[i * 9 + 5]);
				c = vec3(arr[i * 9 + 6], arr[i * 9 + 7], arr[i * 9 + 8]);
				tmp = IntersectTriangle(ray, a, b, c);
				if (t1.t > tmp.t){
					t1 = tmp;
				}
			}

			// 2번 큐브를 계산합니다 연두색
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
				// 광선의 반사벡터를 구한다
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