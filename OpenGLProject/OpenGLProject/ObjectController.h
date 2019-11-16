#pragma once
#include <string>
#include <map>
#include "Object.h"
#include "Shader.h"

class ObjectController
{
private:
	/*
		������Ʈ���� ��Ƶδ� map�Դϴ�
		Key�� String�� ���ϸ��� ����ϰ� Value�� Object��ü �ϳ��� ����մϴ�
	*/
	static std::map<std::string, Object> s_object; 
private:
	static int s_iNumGenList; // GenList�� ����
public:
	static void LoadObject(const Shader& shader, const char* fdir); // ���� ����� obj������ �ҷ��� Object�� �����մϴ�
	static Object FindObject(const std::string key); // key�� Object�� ã�Ƽ� ��ȯ�մϴ�
	static void DrawObjects(const Shader& shader); // ��� Object�� �׸��ϴ� Shader Program�� progId�� �����մϴ�
private:
	// ObjectController ���ο��� ���̴� �Լ�, Normal ���͸� ����մϴ�
	static void CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};


