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
	void setVec3(const glm::vec3& const vec, const std::string& str) const;
	void setMatirx3(const glm::mat4& const matrix, const std::string& str) const;
	void setMatrix4(const glm::mat4& const matrix, const std::string& str) const;
	void setUniform1(const GLuint& i, const  std::string& str) const;
	void setUniform4f();
	GLuint getID(void) const;
};