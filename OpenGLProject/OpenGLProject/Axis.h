#pragma once
#include <gl\gl.H>
#include <gl\glu.H>
#include <gl/glut.H>
#include <gl\glaux.H>

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLU32.LIB")
#pragma comment(lib, "GLUT32.LIB")

class Axis
{
private:
	// ���� ���
	const static int c_iNumAxis; // ���� ����
public:
	static void Draw(); // ����� �Ǵ� ���� �׸��ϴ�.
};

