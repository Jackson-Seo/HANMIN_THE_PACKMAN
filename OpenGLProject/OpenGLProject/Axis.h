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
	// 정적 상수
	const static int c_iNumAxis; // 축의 개수
public:
	static void Draw(); // 배경이 되는 축을 그립니다.
};

