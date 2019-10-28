#pragma once
#include <gl\gl.H>
#include <gl\glu.H>
#include <gl/glut.H>
#include <gl\glaux.H>

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLU32.LIB")
#pragma comment(lib, "GLUT32.LIB")

// ��������
const static float fCameraMovemet = 0.2778; // Camera�� ȸ���� �ε巴�� ����

class Camera
{
private:
	static CPoint s_CaRo; // ī�޶��� ȸ�� ����
	static CPoint s_CaTrans; // ī�޶��� �̵� ����
public:
	static void Initialize(); // ī�޶��� �ʱ� ��ġ�� ������ �����մϴ�
	static void ReSize(GLsizei width, GLsizei height); // Viewport�� Perspective�� �����ϰ� Projection Matrix�� �ʱ�ȭ�մϴ�
	static void Convert(); // ī�޶� �����̵� �� ȸ���� �����մϴ�
public:
	static void setCaRo(CPoint point);
	static CPoint getCaRo();
};

