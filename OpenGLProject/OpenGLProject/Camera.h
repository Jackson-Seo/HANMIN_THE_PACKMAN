#pragma once

class Camera
{
private:
	// �������
	const static float c_fCameraRotate; // Camera�� ȸ���� �ε巴�� ����
	const static float c_Degree; // Degree�� ��ȯ�ϴ� ��� 
private:
	static CPoint s_CaRo; // ī�޶��� ȸ�� ����
	static float s_X; // ī�޶��� ��ġ X
	static float s_Y; // ī�޶��� ��ġ Y
	static float s_Z; // ī�޶��� ��ġ Z
public:
	static void Initialize(); // ī�޶��� �ʱ� ��ġ�� ������ �����մϴ�
	static void ReSize(GLsizei width, GLsizei height); // Viewport�� Perspective�� �����ϰ� Projection Matrix�� �ʱ�ȭ�մϴ�
	static void Convert(); // ī�޶� �����̵� �� ȸ���� �����մϴ�
	static void Move(float x, float y, float z); // ī�޶��� ���⿡ ���� �����̵� ��ġ�� ����մϴ�
public:
	static void setCaRo(CPoint point);
	static CPoint getCaRo();
};

