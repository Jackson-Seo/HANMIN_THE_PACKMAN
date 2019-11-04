#pragma once
#include <string>
#include <fstream>

namespace Core {
	static GLuint programId;
	void InitShaders();
	char* textFromFile(const char* filePathName, int& textLength);
}