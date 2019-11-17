#pragma once

// ī�޶� �����̴� �����Դϴ�
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
	// �������
	const static float c_velocity; // ī�޶��� �̵��ӷ�
	const static float c_fCameraRotate; // Camera�� ȸ���� �ε巴�� ����
private:
	static glm::vec3 vPosition; // ī�޶� ��ġ
	static glm::vec3 vFront; // ī�޶� ���� ����
	static glm::vec3 vRight; // ī�޶� ���� ����
	static glm::vec3 vUp; // ī�޶� ���� ����
	static float fYaw; // Yaw ȸ�� ����
	static float fPitch; // Pitch ȸ�� ����
public:
	static void Initialize(void); // ī�޶��� ��ġ�� ������ �����մϴ�
	static glm::mat4 getViewMatrix(void);
	static void Move(Direction direction, double deltaTime); // ī�޶� direction �������� �̵���ŵ�ϴ�
	static void Rotate(CPoint point, double deltaTime); // ī�޶� ȸ����ŵ�ϴ�
};
