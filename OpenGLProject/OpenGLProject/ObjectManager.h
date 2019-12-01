#pragma once
#include "Object.h"
#include "Shader.h"

const int MAXOBJ = 100;


class ObjectManager
{
private:
	static float initObjPos[3];
	static int ObjID[MAXOBJ];
	static int idIndex;

	/*
		오브젝트들을 담아두는 map입니다
		Key인 String은 파일명을 사용하고 Value는 Object객체 하나를 사용합니다
	*/
public:
	static std::string objIDS[MAXOBJ];
	static std::map<int, Object> s_object;
private:
	static int s_iNumGenList; // GenList의 개수
public:
	static void LoadObject(const Shader& shader, const char* fdir, int objid); // 파일 경로의 obj파일을 불러서 Object에 저장합니다
	static Object FindObject(const int key); // key로 Object를 찾아서 반환합니다
	static void DrawObjects(const Shader& shader); // 모든 Object를 그립니다 Shader Program를 progId로 지정합니다
private:
	// ObjectManager 내부에서 쓰이는 함수, Normal 벡터를 계산합니다
	static void CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};
