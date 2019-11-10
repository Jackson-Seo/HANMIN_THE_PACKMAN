#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static time_t time;
	static time_t deltaTime; // �����Ӱ� �ð� ����
	static bool bRClick; // ���콺 ��Ŭ�� ����
	static bool bLClick; // ���콺 ��Ŭ�� ����
	static CPoint clickPoint; // ���콺 Ŭ�� ��ġ
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
