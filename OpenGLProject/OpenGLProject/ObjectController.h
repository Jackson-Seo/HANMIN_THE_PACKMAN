#pragma once
#include <string>
#include <map>
#include "Object.h"

class ObjectController
{
private:
	static std::map<std::string, Object> s_object; // ������Ʈ ����
public:
	static void AddObject(std::string key, Object value); // ������Ʈ�� �ʿ� �߰�
};