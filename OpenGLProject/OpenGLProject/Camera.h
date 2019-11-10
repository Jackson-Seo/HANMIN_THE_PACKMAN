#pragma once

enum class Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
private:
	// 정적상수
	const static float c_velocity; // 카메라의 이동속력
	const static float c_fCameraRotate; // Camera의 회전을 부드럽게 보정
	const static float c_Degree; // Degree로 변환하는 상수
private:
	static glm::vec3 vPosition; // 카메라 위치
	static glm::vec3 vFront; // 카메라 정면 벡터
	static glm::vec3 vRight; // 카메라 우측 벡터
	static glm::vec3 vUp; // 카메라 위측 벡터
public:
	static void Initialize(void); // 카메라의 초기 위치와 방향을 지정합니다
	static void Move(Direction direction, double deltaTime);
	static glm::mat4 getViewMatrix(void);
};
