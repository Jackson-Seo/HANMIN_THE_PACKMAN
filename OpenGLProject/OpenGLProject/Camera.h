#pragma once
#include <gl\gl.H>
#include <gl\glu.H>
#include <gl/glut.H>
#include <gl\glaux.H>

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLU32.LIB")
#pragma comment(lib, "GLUT32.LIB")

// 전역변수
const static float fCameraMovemet = 0.2778; // Camera의 회전을 부드럽게 보정

class Camera
{
private:
	static CPoint s_CaRo; // 카메라의 회전 각도
	static CPoint s_CaTrans; // 카메라의 이동 각도
public:
	static void Initialize(); // 카메라의 초기 위치와 방향을 지정합니다
	static void ReSize(GLsizei width, GLsizei height); // Viewport와 Perspective를 설정하고 Projection Matrix를 초기화합니다
	static void Convert(); // 카메라에 평행이동 후 회전을 적용합니다
public:
	static void setCaRo(CPoint point);
	static CPoint getCaRo();
};

