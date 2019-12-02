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

// 카메라의 위치와 방향을 토대로 view matrix를 계산합니다 후에 vertex shader의 view Uniform 변수로 넘깁니다
mat4 _Camera_Base_::getViewMatrix(void)
{
	return lookAt(vPosition, vPosition + vGaze, vUp);
}

void _Camera_Base_::Initialize(struct Control_info* info)
{
	Rotate(info->clickPoint, 1.3f);
}

/*
	프레임의 시간차와 속력을 곱한 이동거리만큼 카메라를 direction 방향으로 이동시킵니다
	방향은 유지시키고 방향에 따라 카메라의 위치만 변화시킵니다
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
	카메라를 회전시킵니다 point의 x값이 Yaw의 회전각도가 되고
	point의 y값이 Pitch의 회전각도가 됩니다
	Yaw와 Pitch의 각도에 따라 카메라가 바라보는 방향인 vFront벡터를 회전시킵니다
	카메라가 바라보는 방향만 알면 외적을 통해 카메라의 오른쪽과 위쪽의 벡터를 계산할 수 있습니다
*/
void _Camera_Base_::Rotate(CPoint point, double deltaTime) {
	vec3 front;
	fYaw += deltaTime * point.x * c_fCameraRotate;
	fPitch -= deltaTime * point.y * c_fCameraRotate;
	// Pitch의 각도가 90도 넘어가면 카메라가 반대방향으로 넘어가니 이를 막습니다
	if (fPitch > 89.9999f)
		fPitch = 89.9999f;
	if (fPitch < -89.9999f)
		fPitch = -89.9999f;
	// Yaw와 Pitch의 각도에 따라 카메라가 바라보는 방향인 vFront벡터를 회전시킵니다
	front.x = cos(radians(fYaw)) * cos(radians(fPitch));
	front.y = sin(radians(fPitch));
	front.z = sin(radians(fYaw)) * cos(radians(fPitch));

	// 방향벡터를 계산합니다
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