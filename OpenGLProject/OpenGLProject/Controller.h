#pragma once
#include <afxwin.h>
/*
	���콺 �� Ű���� ���� ��Ʈ�� ó���� �� Ŭ�������� �ٷ�ϴ�
	MFC���� �޽����� �ٷ� �ޱ����� CWnd�� ��������� ����� ���� �ʽ��ϴ�
	�޽����� �ٷ� ���� �� �����Ƿ� �޽����� OpenGLProjectView.cpp���� �ް� �ű⼭ �� Ŭ������ ȣ���մϴ�
*/
class Controller : public CWnd
{
private:
	static clock_t time; // deltaTime�� ����ϱ� ���� ������ time_t�� ����
	static clock_t deltaTime; // �����Ӱ� �ð� ����
	static bool bRClick; // ���콺 ��Ŭ�� ����
	static bool bLClick; // ���콺 ��Ŭ�� ����
	static CPoint clickPoint; // ���콺�� �����ؼ� �̵��� �Ÿ�
	static CPoint preClickPoint; // ���콺 �̵����� ���� �̵� ��ġ
public:
	static void Initialize(void);
	static void Clock(void);
public:
	static void OnMouseMove(UINT nFlags, CPoint point);
	static void OnRButtonDown(UINT nFlags, CPoint point);
	static void OnRButtonUp(UINT nFlags, CPoint point);
	static void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
