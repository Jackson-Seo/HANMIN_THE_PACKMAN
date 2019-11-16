#include "pch.h"
#include "Light.h"

Light::Light()
{
}

Light::Light(const Shader& shader, float x, float y, float z, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) : m_x(x), m_y(y), m_z(z) {
	// Shader�� �Ʒ��� �ش��ϴ� �׸���� �־�� ����˴ϴ�
	shader.setVec3(glm::vec3(x, y, z) , "Light.position");
	shader.setVec3(ambient, "Light.ambient");
	shader.setVec3(diffuse, "Light.ambient");
	shader.setVec3(specular, "Light.ambient");
}

// Ambient, Diffuse, Specular ���� �޾Ƽ� Shader�� �����ŵ�ϴ�
void Light::setAmbient(const Shader& shader, const glm::vec3& vec) { shader.setVec3(vec, "Light.ambient"); }
void Light::setDiffuse(const Shader& shader, const glm::vec3& vec) { shader.setVec3(vec, "Light.diffuse"); }
void Light::setSpecular(const Shader& shader, const glm::vec3& vec) { shader.setVec3(vec, "Light.specular"); }