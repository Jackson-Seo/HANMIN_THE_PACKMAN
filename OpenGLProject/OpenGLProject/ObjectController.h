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
	static void LoadObject(const char* const fdir);
	static void DrawObjects(void);
};