#pragma once
#include <string>
#include <map>
#include "Object.h"
#include "Shader.h"

class ObjectController
{
private:
	static std::map<std::string, Object> s_object; // 오브젝트 관리
private:
	static int s_iNumGenList; // GenList의 개수
public:
	static void AddObject(std::string key, Object value); // 오브젝트를 맵에 추가
	static void LoadObject(Shader& shader, const char* const fdir); // 파일 경로의 obj파일을 불러서 Object에 저장합니다
	static Object FindObject(const std::string key); // key로 Object를 찾아서 반환합니다
	static void DrawObjects(GLuint progId); // 모든 Object를 그립니다 Shader Program를 progId로 지정합니다
private:
	// ObjectController 내부에서 쓰이는 함수
	static void CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};