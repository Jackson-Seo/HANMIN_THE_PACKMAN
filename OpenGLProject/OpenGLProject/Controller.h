#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static BOOL s_bRClick; // ���콺 ��Ŭ�� ����
	static BOOL s_bLClick; // ���콺 ��Ŭ�� ����
	static CPoint s_ClickPoint; // ���콺 Ŭ�� ��ġ
	static CPoint s_preClickPoint; // ���콺 �̵����� ���� �̵� ��ġ
public:
	static void setRClick(BOOL b);
	static BOOL getRClick();
	static void setLClick(BOOL b);
	static BOOL getLClick();
	static void setClickPoint(CPoint point);
	static CPoint getClickPoint();
	static void setpreClickPoint(CPoint point);
	static CPoint getpreClickPoint();
};

