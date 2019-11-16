#include "pch.h"
#include "Controller.h"
#include "Camera.h"

// �������� �ʱ�ȭ
clock_t Controller::time = 0.0;
clock_t Controller::deltaTime = 0.0;
bool Controller::bRClick = FALSE;
bool Controller::bLClick = FALSE;
CPoint Controller::clickPoint = { 0, 0 };
CPoint Controller::preClickPoint = { 0, 0 };

// OpenGLProjectView�� initGL���� ȣ����� �ʱ�ȭ ��ŵ�ϴ�
void Controller::Initialize(void) {
	time = clock();
}

/*
	OpenGLProjectView�� DrawGLScene���� ȣ����� �����Ӱ� �ð����� ����մϴ�
	���콺�� ������ �Ÿ���ŭ ī�޶� ȸ����ŵ�ϴ�
*/
void Controller::Clock(void) {
	clock_t newTime = clock();
	deltaTime = newTime - time;
	time = newTime;
	// TRACE1("%lf\n", (double)deltaTime);
	
	// deltaTime��ŭ ȸ����Ű�� ������ deltaTime�� ����� ����� �ȵǹǷ� ������� �Ѱ��ݴϴ�
	Camera::Rotate(clickPoint, 1.3f);
	clickPoint = { 0, 0 };
}

void Controller::OnMouseMove(UINT nFlags, CPoint point)
{
	/*
		if�� : ��Ŭ���� �� ���¿��� �巡�װ� �Ͼ�°�?
		TRUE : ���콺�� ���� �̵��� �Ÿ��� ����մϴ�
	*/
	if (bRClick) {
		clickPoint += point - preClickPoint;
		preClickPoint = point;
	}
}

void Controller::OnRButtonDown(UINT nFlags, CPoint point)
{
	bRClick = true;
	clickPoint = { 0, 0 };
	preClickPoint = point;
}

void Controller::OnRButtonUp(UINT nFlags, CPoint point)
{
	bRClick = false;
}
// �Էµ� Ű�� ���� ī�޶� �ش� �������� �����Դϴ�
void Controller::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case 'W':
		Camera::Move(Direction::FORWARD, (double)deltaTime);
		break;
	case 'A':
		Camera::Move(Direction::LEFT, (double)deltaTime);
		break;
	case 'S':
		Camera::Move(Direction::BACKWARD, (double)deltaTime);
		break;
	case 'D':
		Camera::Move(Direction::RIGHT, (double)deltaTime);
		break;
	case 'Q':
		Camera::Move(Direction::UP, (double)deltaTime);
		break;
	case 'E':
		Camera::Move(Direction::DOWN, (double)deltaTime);
		break;
	}
}