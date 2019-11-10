#include "pch.h"
#include "Camera.h"

// 정적변수 초기화
const float Camera::c_velocity = 0.01;
const float Camera::c_fCameraRotate = 0.2778f;
const float Camera::c_Degree = 3.141592 / 180;
glm::vec3 Camera::vPosition = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 Camera::vFront = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Camera::vRight = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Camera::vUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 카메라 위치와 각 방향을 초기화합니다
void Camera::Initialize(void) {
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vFront = glm::vec3(1.0f, 0.0f, 0.0f);
	vRight = glm::vec3(0.0f, 0.0f, 1.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

// 프레임의 시간차와 속력을 곱한 이동거리만큼 카메라를 direction 방향으로 이동시킵니다
void Camera::Move(Direction direction, double deltaTime) {
	float distance = c_velocity * deltaTime;
	TRACE1("%f\n",distance);

	if (direction == Direction::FORWARD)
		vPosition += vFront * distance;
	if (direction == Direction::BACKWARD)
		vPosition -= vFront * distance;
	if (direction == Direction::RIGHT)
		vPosition += vRight * distance;
	if (direction == Direction::LEFT)
		vPosition -= vRight * distance;
	if (direction == Direction::UP)
		vPosition += vUp * distance;
	if (direction == Direction::DOWN)
		vPosition -= vUp * distance;
}

glm::mat4 Camera::getViewMatrix(void) {
	return glm::lookAt(vPosition, vPosition + vFront, vUp);
}