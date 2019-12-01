#include "pch.h"
#include "IOManager.h"

IOManager::IOManager()
{
	TRACE0("\nIOManager �ʱ�ȭ\n");
	info = { FALSE, FALSE, {0,0},{0,0} };
	this->width = 0;
	this->height = 0;
	ControllTarget = nullptr;
}

/*
	OpenGLProjectView�� DrawGLScene���� ȣ����� �����Ӱ� �ð����� ����մϴ�
	���콺�� ������ �Ÿ���ŭ ī�޶� ȸ����ŵ�ϴ�
*/
// deltaTime��ŭ ȸ����Ű�� ������ deltaTime�� ����� ����� �ȵǹǷ� ������� �Ѱ��ݴϴ�

Control_info* IOManager::GetControl_info(void)
{
	return &info;
}

void IOManager::Initialize(ShaderManager* shaderManager) {
	this->shaderManager = shaderManager;
}

void IOManager::OnSize(UINT nType, int cx, int cy) {
	this->width = cx;
	this->height = cy;
}

void IOManager::OnMouseMove(UINT nFlags, CPoint point)
{
	/*
		if�� : ��Ŭ���� �� ���¿��� �巡�װ� �Ͼ�°�?
		TRUE : ���콺�� ���� �̵��� �Ÿ��� ����մϴ�
	*/
	if (info.bRClick) {
		info.clickPoint += point - info.preClickPoint;
		info.preClickPoint = point;
	}
}

void IOManager::OnRButtonDown(UINT nFlags, CPoint point)
{
	info.bRClick = true;
	info.clickPoint = { 0, 0 };
	info.preClickPoint = point;
}

void IOManager::OnRButtonUp(UINT nFlags, CPoint point)
{
	info.bRClick = false;
}

// �Էµ� Ű�� ���� ī�޶� �ش� �������� �����Դϴ�
void IOManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case 'W':
		ControllTarget->Move(Direction::FORWARD, (double)_SystemMangement_::deltaTime);
		break;
	case 'A':
		ControllTarget->Move(Direction::LEFT, (double)_SystemMangement_::deltaTime);
		break;
	case 'S':
		ControllTarget->Move(Direction::BACKWARD, (double)_SystemMangement_::deltaTime);
		break;
	case 'D':
		ControllTarget->Move(Direction::RIGHT, (double)_SystemMangement_::deltaTime);
		break;
	case 'Q':
		ControllTarget->Move(Direction::UP, (double)_SystemMangement_::deltaTime);
		break;
	case 'E':
		ControllTarget->Move(Direction::DOWN, (double)_SystemMangement_::deltaTime);
		break;
	}
}

void IOManager::OnShaderPhongShading(void) {
	this->shaderManager->rtxON = false;
}

void IOManager::OnShaderRayTracingRendering(void) {
	this->shaderManager->rtxON = !this->shaderManager->rtxON;
}

void IOManager::OnUpdateShaderPhongshading(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(!shaderManager->rtxON);
}

void IOManager::OnUpdateShaderRaytracingrendering(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(shaderManager->rtxON);
}

void IOManager::AttachTarget(ObjectBase* obj)
{
	ControllTarget = obj;
}

ObjectBase* IOManager::GetControllTarget(void)
{
	return ControllTarget;
}