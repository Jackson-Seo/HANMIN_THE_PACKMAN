#include "pch.h"
#include "Camera.h"

using namespace CameraProperties;

//Setting Camera properties ..

const float c_velocity = 0.1f;
const float c_fCameraRotate = 0.2778f;

// Binding default Camera position and direction..
_Camera_Base_::_Camera_Base_()
{
	SetCameraPos(vec3(0.0, 0.0, 0.0));
	SetCameraDirVec(vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
}

// ī�޶��� ��ġ�� ������ ���� view matrix�� ����մϴ� �Ŀ� vertex shader�� view Uniform ������ �ѱ�ϴ�
mat4 _Camera_Base_::getViewMatrix(void)
{
	return lookAt(vPosition, vPosition + vGaze, vUp);
}

void _Camera_Base_::Initialize(struct Control_info* info)
{
	Rotate(info->clickPoint, 1.3f);
}

/*
	�������� �ð����� �ӷ��� ���� �̵��Ÿ���ŭ ī�޶� direction �������� �̵���ŵ�ϴ�
	������ ������Ű�� ���⿡ ���� ī�޶��� ��ġ�� ��ȭ��ŵ�ϴ�
*/
void _Camera_Base_::Move(Direction direction, double deltaTime, float scale) {
	float distance = 0.1;

	if (direction == Direction::FORWARD)
		vPosition += vGaze * distance;
	if (direction == Direction::BACKWARD)
		vPosition -= vGaze * distance;
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
void _Camera_Base_::Rotate(CPoint point, double deltaTime) {
	vec3 front;
	fYaw += deltaTime * point.x * c_fCameraRotate;
	fPitch -= deltaTime * point.y * c_fCameraRotate;
	// Pitch�� ������ 90�� �Ѿ�� ī�޶� �ݴ�������� �Ѿ�� �̸� �����ϴ�
	if (fPitch > 89.9999f)
		fPitch = 89.9999f;
	if (fPitch < -89.9999f)
		fPitch = -89.9999f;
	// Yaw�� Pitch�� ������ ���� ī�޶� �ٶ󺸴� ������ vFront���͸� ȸ����ŵ�ϴ�
	front.x = cos(radians(fYaw)) * cos(radians(fPitch));
	front.y = sin(radians(fPitch));
	front.z = sin(radians(fYaw)) * cos(radians(fPitch));

	// ���⺤�͸� ����մϴ�
	vGaze = normalize(front);
	vRight = normalize(cross(vGaze, vec3(0.0f, 1.0f, 0.0f)));
	vUp = normalize(cross(vRight, vGaze));
}

void CameraProperties::_Camera_Base_::SetCameraPos(vec3 pos)
{
	vPosition = pos;
}

void _Camera_Base_::SetCameraDirVec(vec3 gaze, vec3 right, vec3 left, vec3 up)
{
	vGaze = gaze;
	vRight = right;
	vLeft = left;
	vUp = up;
}

void CameraProperties::_Camera_Base_::SetAngle(float yaw, float pitch, float roll)
{
	fYaw = yaw, fPitch = pitch, fRoll = roll;
}

vec3 CameraProperties::_Camera_Base_::GetProperties(ecProperties properties)
{
	switch (properties)
	{
	case ecProperties::POS: {
		return vPosition;
	}
	case ecProperties::GAZE: {
		return vGaze;
	}
	case ecProperties::RIGHT: {
		return vRight;
	}
	case ecProperties::LEFT: {
		return vLeft;
	}
	case ecProperties::UP: {
		return vUp;
	}
	}
}