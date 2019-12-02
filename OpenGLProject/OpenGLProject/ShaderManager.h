#pragma once
#include "Shader.h"

/*
	Shader 객체를 관리하고 어느 Shader가 사용될지를 결정하는 클래스입니다
	OpenGLProjectView와 IOManager에서 사용됩니다
*/
class ShaderManager
{
private:
	// 싱글톤 패턴을 위한 flag입니다
	static bool singletonFlag;
public:
	// Ray Tracing 렌더링을 적용할지를 결정합니다
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