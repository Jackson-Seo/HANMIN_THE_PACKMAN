#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static bool s_bRClick; // ���콺 ��Ŭ�� ����
	static bool s_bLClick; // ���콺 ��Ŭ�� ����
	static CPoint s_ClickPoint; // ���콺 Ŭ�� ��ġ
	static CPoint s_preClickPoint; // ���콺 �̵����� ���� �̵� ��ġ
public:
	static void setRClick(bool b);
	static bool getRClick();
	static void setLClick(bool b);
	static bool getLClick();
	static void setClickPoint(CPoint point);
	static CPoint getClickPoint();
	static void setpreClickPoint(CPoint point);
	static CPoint getpreClickPoint();
};
