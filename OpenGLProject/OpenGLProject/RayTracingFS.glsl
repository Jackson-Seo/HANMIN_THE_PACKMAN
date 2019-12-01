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
	// 광선을 Pixel을 향해 쏩니다
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
		if문 : 광선이 충돌하는지 계산합니다
		else if문 : 카메라가 구 안에 있는지 계산합니다
		else문 : 광선이 구와 충돌하고 카메라가 구 밖에 있습니다
	*/
	if (s < 0) {
		result = texture(skybox, o_TextureCoords);
	} else if (m2 > r2) {
		result = texture(skybox, o_TextureCoords);
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
		vec3 intersection = ray.origin + dist * ray.direction;
		// 교차점의 법선벡터를 구한다
		vec3 normal = normalize(intersection - sphere.position);
		// 광원에서의 입사벡터를 구한다
		vec3 lightDir = normalize(light.position - intersection);
		// 광선의 반사벡터를 구한다
		vec3 rayReflection = normalize(vec3(inverse(u_View) * vec4(reflect(ray.direction, normal),1)));
		vec3 viewDir = normalize(vec3(0,0,0) - intersection);
		// 광원에서의 입사벡터의 반사벡터를 구한다
		vec3 lightReflection = normalize(reflect(-lightDir, normal));
		// diffuse 상수를 구한다
		float diff = max(dot(lightDir, normal), 0.0);
		// specular 상수를 구한다
		float spec = pow(max(dot(viewDir, lightReflection), 0.0f), 30);

		diffuse = vec4(light.diffuse * diff * material.diffuse, 1.0f);
		specular = vec4(light.specular * spec * material.specular, 1.0f);
		result += diffuse + specular;
	}
   fragmentColor = result;
}