#include "pch.h"
#include "ShaderManager.h"

bool ShaderManager::singletonFlag = false;

ShaderManager::ShaderManager(void) {
	TRACE0("\nShaderManager 생성자 호출\n");
	assert(!singletonFlag);

	rtxON = false;
	// Shader 객체를 생성합니다. 인자로 넘겨주는 string에 해당하는 glsl파일을 쉐이더로 사용합니다
	glslShader = Shader("LightingVertexShader.glsl", "LightingFragmentShader.glsl");
	skyboxShader = Shader("SkyboxVS.glsl", "SkyboxFS.glsl");
	rayTracingShader = Shader("SkyboxVS.glsl", "RayTracingFS.glsl");
	// gpgpuShader = Shader("VertexGPGPUVS.glsl", "VertexGPGPUFS.glsl");

	singletonFlag = true;
}

void ShaderManager::InitGPGPU(void) {

}