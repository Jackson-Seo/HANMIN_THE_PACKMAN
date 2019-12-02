#pragma once
#include "Shader.h"

/*
	Shader ��ü�� �����ϰ� ��� Shader�� �������� �����ϴ� Ŭ�����Դϴ�
	OpenGLProjectView�� IOManager���� ���˴ϴ�
*/
class ShaderManager
{
private:
	// �̱��� ������ ���� flag�Դϴ�
	static bool singletonFlag;
public:
	// Ray Tracing �������� ���������� �����մϴ�
	bool rtxON;
	Shader glslShader;
	Shader skyboxShader;
	Shader rayTracingShader;
	Shader gpgpuShader;
public:
	ShaderManager(void);
private:
	void InitGPGPU(void);
};