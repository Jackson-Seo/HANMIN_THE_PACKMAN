#include "pch.h"
#include "Light.h"

Light::Light(Shader shader) : shader(shader) {}

void Light::test() {
	shader.setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");
}
