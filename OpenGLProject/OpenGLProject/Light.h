#pragma once
#include "Shader.h"

class Light
{
private:
	Shader shader;
public:
	Light(Shader shader);
	void test();
};

