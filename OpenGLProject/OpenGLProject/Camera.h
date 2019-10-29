#pragma once
#include <gl\gl.H>
#include <gl\glu.H>
#include <gl/glut.H>
#include <gl\glaux.H>

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLU32.LIB")
#pragma comment(lib, "GLUT32.LIB")

class Camera
{
private:
	// �������
	const static float c_fCameraRotate; // Camera�� ȸ���� �ε巴�� ����
	const static float c_fCameraTrans; // Camera�� �����̵��� ����
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
	static void Move(int x, int y, int z); // ī�޶��� ���⿡ ���� �����̵� ��ġ�� ����մϴ�
public:
	static void setCaRo(CPoint point);
	static CPoint getCaRo();
};

