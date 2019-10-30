#pragma once
#include <string>
#include <map>
#include "Object.h"

class ObjectController
{
private:
	static std::map<std::string, Object> s_object; // 오브젝트 관리
private:
	static int s_iNumGenList; // GenList의 개수
public:
	static void AddObject(std::string key, Object value); // 오브젝트를 맵에 추가
	static void LoadObject(const char* const fdir);
	static void DrawObjects(void);
};