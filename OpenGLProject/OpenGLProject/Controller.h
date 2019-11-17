#pragma once
#include "ObjectBase.h"
#include "SystemMangement.h"
#include <afxwin.h>
/*
	���콺 �� Ű���� ���� ��Ʈ�� ó���� �� Ŭ�������� �ٷ�ϴ�
	MFC���� �޽����� �ٷ� �ޱ����� CWnd�� ��������� ����� ���� �ʽ��ϴ�
	�޽����� �ٷ� ���� �� �����Ƿ� �޽����� OpenGLProjectView.cpp���� �ް� �ű⼭ �� Ŭ������ ȣ���մϴ�
*/

class Controller :public ObjectBase
{
private:

	Control_info info;
	ObjectBase* ControllTarget;
	
public:
	Controller();
	~Controller() {};

public:
	Control_info* GetControl_info(void);

public:
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void AttachTarget(ObjectBase* obj);
	ObjectBase* GetControllTarget(void);
};
