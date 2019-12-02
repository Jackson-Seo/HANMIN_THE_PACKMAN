#include "pch.h"
#include "IOManager.h"

IOManager::IOManager()
{
	TRACE0("\nIOManager 초기화\n");
	info = { FALSE, FALSE, {0,0},{0,0} };
	this->width = 0;
	this->height = 0;
	ControllTarget = nullptr;
}

/*
	OpenGLProjectView의 DrawGLScene에서 호출시켜 프레임간 시간차를 계산합니다
	마우스가 움직인 거리만큼 카메라를 회전시킵니다
*/
// deltaTime만큼 회전시키려 했으나 deltaTime이 제대로 계산이 안되므로 상수값을 넘겨줍니다

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
		if문 : 우클릭이 된 상태에서 드래그가 일어났는가?
		TRUE : 마우스가 누적 이동한 거리를 계산합니다
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

// 입력된 키에 따라서 카메라를 해당 방향으로 움직입니다
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