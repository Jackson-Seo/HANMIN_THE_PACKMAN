#include "pch.h"
#include "Camera.h"

// �������� �ʱ�ȭ
const float Camera::c_velocity = 0.1;
const float Camera::c_fCameraRotate = 0.2778f;
glm::vec3 Camera::vPosition = glm::vec3(0.0f, 2.0f, 0.0f);
glm::vec3 Camera::vFront = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Camera::vRight = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Camera::vUp = glm::vec3(0.0f, 1.0f, 0.0f);
float Camera::fYaw = 0.0f;
float Camera::fPitch = 0.0f;

// ī�޶� ��ġ�� �� ������ �����մϴ�
void Camera::Initialize(void) {
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vFront = glm::vec3(1.0f, 0.0f, 0.0f);
	vRight = glm::vec3(0.0f, 0.0f, 1.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

// ī�޶��� ��ġ�� ������ ���� view matrix�� ����մϴ� �Ŀ� vertex shader�� view Uniform ������ �ѱ�ϴ�
glm::mat4 Camera::getViewMatrix(void) {
	return glm::lookAt(vPosition, vPosition + vFront, vUp);
}

/*
	�������� �ð����� �ӷ��� ���� �̵��Ÿ���ŭ ī�޶� direction �������� �̵���ŵ�ϴ�
	������ ������Ű�� ���⿡ ���� ī�޶��� ��ġ�� ��ȭ��ŵ�ϴ�
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
	ī�޶� ȸ����ŵ�ϴ� point�� x���� Yaw�� ȸ�������� �ǰ�
	point�� y���� Pitch�� ȸ�������� �˴ϴ�
	Yaw�� Pitch�� ������ ���� ī�޶� �ٶ󺸴� ������ vFront���͸� ȸ����ŵ�ϴ�
	ī�޶� �ٶ󺸴� ���⸸ �˸� ������ ���� ī�޶��� �����ʰ� ������ ���͸� ����� �� �ֽ��ϴ�
*/
void Camera::Rotate(CPoint point, double deltaTime) {
	glm::vec3 front;
	fYaw += deltaTime * point.x * c_fCameraRotate;
	fPitch -= deltaTime * point.y * c_fCameraRotate;
	// Pitch�� ������ 90�� �Ѿ�� ī�޶� �ݴ�������� �Ѿ�� �̸� �����ϴ�
	if (fPitch > 89.9999f)
		fPitch = 89.9999f;
	if (fPitch < -89.9999f)
		fPitch = -89.9999f;
	// Yaw�� Pitch�� ������ ���� ī�޶� �ٶ󺸴� ������ vFront���͸� ȸ����ŵ�ϴ�
	front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	front.y = sin(glm::radians(fPitch));
	front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));

	// ���⺤�͸� ����մϴ�
	vFront = glm::normalize(front);
	vRight = glm::normalize(glm::cross(vFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	vUp = glm::normalize(glm::cross(vRight, vFront));
}