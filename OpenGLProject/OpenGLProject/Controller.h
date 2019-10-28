#pragma once
#include <afxwin.h>

class Controller : public CWnd
{
private:
	static bool s_bRClick; // ���콺 ��Ŭ�� ����
	static bool s_bLClick; // ���콺 ��Ŭ�� ����
	static CPoint s_ClickPoint; // ���콺 Ŭ�� ��ġ
	static CPoint s_preClickPoint; // ���콺 �̵����� ���� �̵� ��ġ
	static bool s_bW; // WŰ ����
	static bool s_bA; // AŰ ����
	static bool s_bS; // SŰ ����
	static bool s_bD; // DŰ ����
public:
	static void CameraTrans(); // WASD Ű�� ���� ī�޶� �����̵� �մϴ�
public:
	static void setRClick(bool b);
	static bool getRClick();
	static void setLClick(bool b);
	static bool getLClick();
	static void setClickPoint(CPoint point);
	static CPoint getClickPoint();
	static void setpreClickPoint(CPoint point);
	static CPoint getpreClickPoint();
	static void setW(bool b);
	static bool getW();
	static void setA(bool b);
	static bool getA();
	static void setS(bool b);
	static bool getS();
	static void setD(bool b);
	static bool getD();
};

