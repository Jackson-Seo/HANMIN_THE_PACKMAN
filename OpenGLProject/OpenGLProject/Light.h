#pragma once
#include "Shader.h"

class Light
{
private:
	float m_x = 0, m_y = 0, m_z = 0; // 월드에서의 위치
public:
	/*
		생성자는 광원의 위치, ambient, diffuse, specular 값을 Shader에 넘겨줍니다
		Light를 적용시키려면 이를 지원하는 Shader를 사용해야합니다
	*/
	Light();
	Light(const Shader& shader, float x, float y, float z, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
	void setAmbient(const Shader& shader, const glm::vec3& vec);
	void setDiffuse(const Shader& shader, const glm::vec3& vec);
	void setSpecular(const Shader& shader, const glm::vec3& vec);
};