//���� ��ü�� �ð��� tick per frame �� �����մϴ�. (Controller �� clock() �Լ��� ����� �̵�����)
//���� �޸� ������ å�����ϴ�.

#pragma once
#include <afxwin.h>
#include <random>
#include <iostream>
using namespace std;

class _SystemMangement_
{
public:
	static clock_t time; // deltaTime�� ����ϱ� ���� ������ time_t�� ����
	static clock_t deltaTime; // �����Ӱ� �ð� ����
	static bool bCameraOn;     //ī�޶� ��� on/off
	static bool bObjectOn;     // ������Ʈ �̵� on/off
	static bool blightOn;      // ����Ʈ �̵� on/off

public:

	static float getRandomNumber(float min, float max);
	static void initSystem(void);
	static void Clock(void);
};
