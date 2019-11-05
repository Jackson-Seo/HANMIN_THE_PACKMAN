#pragma once
#include <string>
#include <map>
#include "Object.h"

class ObjectController
{
private:
	static std::map<std::string, Object> s_object; // ������Ʈ ����
private:
	static int s_iNumGenList; // GenList�� ����
public:
	static void AddObject(std::string key, Object value); // ������Ʈ�� �ʿ� �߰�
	static void LoadObject(const char* const fdir); // ���� ����� obj������ �ҷ��� Object�� �����մϴ�
	static Object FindObject(const std::string key); // key�� Object�� ã�Ƽ� ��ȯ�մϴ�
	static void DrawObjects(void); // ��� Object�� �׸��ϴ�
private:
	// ObjectController ���ο��� ���̴� �Լ�
	static void CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};