#pragma once
#include <fstream>
#include <sstream>
#include "DebugOutput.h"

class Shader
{
private:
	// program ID
	GLuint ID;
public:
	// 생성자는 shader를 읽고 생성합니다.
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	// shader를 활성화하고 사용합니다 shader를 사용하려면 반드시 호출해야 합니다
	void use();
	// Uniform 유틸리티 함수들 Shader의 Uniform 변수에 값을 전달할때 사용합니다
	void setfloat(const GLfloat& value, const std::string& str) const;
	void setVec3(const glm::vec3& vec, const std::string& str) const;
	void setVec4(const glm::vec4& vec, const std::string& str) const;
	void setMatirx3(const glm::mat4& matrix, const std::string& str) const;
	void setMatrix4(const glm::mat4& matrix, const std::string& str) const;
	void setUniform1(const GLuint& i, const std::string& str) const;
	// Shader 객체의 Program ID를 받을때 사용합니다
	GLuint getID(void) const;
};