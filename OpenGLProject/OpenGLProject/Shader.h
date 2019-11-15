#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:
	// program ID
	GLuint ID;
public:
	// 생성자는 shader를 읽고 생성합니다.
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	// shader를 활성화하고 사용합니다.
	void use();
	// Uniform 유틸리티 함수들
	void setMatrix(const glm::mat4& matrix, const std::string& str) const;
	void setVec3(const glm::vec3& vec, const std::string& str) const;
	GLuint getID(void);
};