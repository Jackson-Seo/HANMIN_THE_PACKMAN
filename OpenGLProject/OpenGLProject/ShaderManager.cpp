#include "pch.h"
#include "ShaderManager.h"

bool ShaderManager::singletonFlag = false;

ShaderManager::ShaderManager(void) {
	TRACE0("\nShaderManager ������ ȣ��\n");
	assert(!singletonFlag);

	rtxON = false;
	// Shader ��ü�� �����մϴ�. ���ڷ� �Ѱ��ִ� string�� �ش��ϴ� glsl������ ���̴��� ����մϴ�
	glslShader = Shader("LightingVertexShader.glsl", "LightingFragmentShader.glsl");
	skyboxShader = Shader("SkyboxVS.glsl", "SkyboxFS.glsl");
	rayTracingShader = Shader("SkyboxVS.glsl", "RayTracingFS.glsl");
	// gpgpuShader = Shader("VertexGPGPUVS.glsl", "VertexGPGPUFS.glsl");

	singletonFlag = true;
}

void ShaderManager::InitGPGPU(void) {

}