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
		������Ʈ���� ��Ƶδ� map�Դϴ�
		Key�� String�� ���ϸ��� ����ϰ� Value�� Object��ü �ϳ��� ����մϴ�
	*/
public:
	static std::string objIDS[MAXOBJ];
	static std::map<int, Object> s_object;
private:
	static int s_iNumGenList; // GenList�� ����
public:
	static void LoadObject(const Shader& shader, const char* fdir, int objid); // ���� ����� obj������ �ҷ��� Object�� �����մϴ�
	static Object FindObject(const int key); // key�� Object�� ã�Ƽ� ��ȯ�մϴ�
	static void DrawObjects(const Shader& shader); // ��� Object�� �׸��ϴ� Shader Program�� progId�� �����մϴ�
private:
	// ObjectManager ���ο��� ���̴� �Լ�, Normal ���͸� ����մϴ�
	static void CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};
