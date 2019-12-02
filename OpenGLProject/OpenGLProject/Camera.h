#pragma once
#include "ObjectBase.h"
using namespace glm;
// 카메라가 움직이는 방향입니다

namespace CameraProperties {
	class _Camera_Base_ :public ObjectBase
	{
	private:

		// Camera postion and vector properties...
		vec3 vPosition;
		vec3 vGaze;
		vec3 vRight;
		vec3 vLeft;
		vec3 vUp;

		// Setting yaw, pitch, roll..
		float fYaw = 0.0;
		float fPitch = 0.0;
		float fRoll = 0.0;

	public:
		_Camera_Base_();
		~_Camera_Base_() {};

	public:
		static enum class ecProperties { POS, GAZE, RIGHT, LEFT, UP };

		//Getter and Setter for Camera properties..

		void SetCameraPos(vec3 pos);
		void SetCameraDirVec(vec3 front, vec3 right, vec3 left, vec3 up);
		void SetAngle(float yaw, float pitch, float roll);

		vec3 GetProperties(ecProperties properties);

		virtual void Initialize(struct Control_info* info) override;
		virtual void Move(Direction direction, double deltaTime, float scale = 1) override;
		virtual void Rotate(CPoint point, double deltaTime) override;

		mat4 getViewMatrix(void);
	};

	class Camera : public _Camera_Base_
	{
	private:
		// Camera properties..
		float c_velocity; // 카메라의 이동속력
		float c_fCameraRotate; // Camera의 회전을 부드럽게 보정

	public:

		void SetCameraSpeed(float speed);
		void SetCameraRotate(float rotate);

		float GetCamVelocity(void);
		float GetCamRotate(void);
	};
}
