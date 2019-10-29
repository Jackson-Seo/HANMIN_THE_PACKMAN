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
	// 정적상수
	const static float c_fCameraRotate; // Camera의 회전을 부드럽게 보정
	const static float c_fCameraTrans; // Camera의 평행이동을 보정
	const static float c_Degree; // Degree로 변환하는 상수 
private:
	static CPoint s_CaRo; // 카메라의 회전 각도
	static float s_X; // 카메라의 위치 X
	static float s_Y; // 카메라의 위치 Y
	static float s_Z; // 카메라의 위치 Z
public:
	static void Initialize(); // 카메라의 초기 위치와 방향을 지정합니다
	static void ReSize(GLsizei width, GLsizei height); // Viewport와 Perspective를 설정하고 Projection Matrix를 초기화합니다
	static void Convert(); // 카메라에 평행이동 후 회전을 적용합니다
	static void Move(int x, int y, int z); // 카메라의 방향에 따른 평행이동 위치를 계산합니다
public:
	static void setCaRo(CPoint point);
	static CPoint getCaRo();
};

