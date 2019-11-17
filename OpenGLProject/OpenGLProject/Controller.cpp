#include "pch.h"
#include "Controller.h"


Controller::Controller()
{
	info = { FALSE, FALSE, {0,0},{0,0} };
}



/*
	OpenGLProjectView�� DrawGLScene���� ȣ����� �����Ӱ� �ð����� ����մϴ�
	���콺�� ������ �Ÿ���ŭ ī�޶� ȸ����ŵ�ϴ�
*/
// deltaTime��ŭ ȸ����Ű�� ������ deltaTime�� ����� ����� �ȵǹǷ� ������� �Ѱ��ݴϴ�


Control_info* Controller::GetControl_info(void)
{
	return &info;
}

void Controller::OnMouseMove(UINT nFlags, CPoint point)
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

void Controller::OnRButtonDown(UINT nFlags, CPoint point)
{
	info.bRClick = true;
	info.clickPoint = { 0, 0 };
	info.preClickPoint = point;
}

void Controller::OnRButtonUp(UINT nFlags, CPoint point)
{
	info.bRClick = false;
}
// �Էµ� Ű�� ���� ī�޶� �ش� �������� �����Դϴ�
void Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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

void Controller::AttachTarget(ObjectBase* obj)
{
	ControllTarget = obj;
}

ObjectBase* Controller::GetControllTarget(void)
{
	return ControllTarget;
}
