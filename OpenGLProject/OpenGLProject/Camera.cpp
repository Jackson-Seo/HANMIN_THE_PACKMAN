#include "pch.h"
#include "Camera.h"

// 정적변수 초기화
const float Camera::c_velocity = 0.1;
const float Camera::c_fCameraRotate = 0.2778f;
glm::vec3 Camera::vPosition = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 Camera::vFront = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Camera::vRight = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Camera::vUp = glm::vec3(0.0f, 1.0f, 0.0f);
float Camera::fYaw = 0.0f;
float Camera::fPitch = 0.0f;

// 카메라 위치와 각 방향을 지정합니다
void Camera::Initialize(void) {
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vFront = glm::vec3(1.0f, 0.0f, 0.0f);
	vRight = glm::vec3(0.0f, 0.0f, 1.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

// 카메라의 위치와 방향을 토대로 view matrix를 계산합니다 후에 vertex shader의 view Uniform 변수로 넘깁니다
glm::mat4 Camera::getViewMatrix(void) {
	return glm::lookAt(vPosition, vPosition + vFront, vUp);
}

/*
	프레임의 시간차와 속력을 곱한 이동거리만큼 카메라를 direction 방향으로 이동시킵니다
	방향은 유지시키고 방향에 따라 카메라의 위치만 변화시킵니다
*/
void Camera::Move(Direction direction, double deltaTime) {
	float distance = c_velocity * deltaTime;

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

/*
	카메라를 회전시킵니다 point의 x값이 Yaw의 회전각도가 되고
	point의 y값이 Pitch의 회전각도가 됩니다
	Yaw와 Pitch의 각도에 따라 카메라가 바라보는 방향인 vFront벡터를 회전시킵니다
	카메라가 바라보는 방향만 알면 외적을 통해 카메라의 오른쪽과 위쪽의 벡터를 계산할 수 있습니다
*/
void Camera::Rotate(CPoint point, double deltaTime) {
	glm::vec3 front;
	fYaw += deltaTime * point.x * c_fCameraRotate;
	fPitch -= deltaTime * point.y * c_fCameraRotate;
	// Pitch의 각도가 90도 넘어가면 카메라가 반대방향으로 넘어가니 이를 막습니다
	if (fPitch > 89.9999f)
		fPitch = 89.9999f;
	if (fPitch < -89.9999f)
		fPitch = -89.9999f;
	// Yaw와 Pitch의 각도에 따라 카메라가 바라보는 방향인 vFront벡터를 회전시킵니다
	front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	front.y = sin(glm::radians(fPitch));
	front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));

	// 방향벡터를 계산합니다
	vFront = glm::normalize(front);
	vRight = glm::normalize(glm::cross(vFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	vUp = glm::normalize(glm::cross(vRight, vFront));
}