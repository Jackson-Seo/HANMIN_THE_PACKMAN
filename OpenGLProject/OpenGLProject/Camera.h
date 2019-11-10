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
	// �������
	const static float c_velocity; // ī�޶��� �̵��ӷ�
	const static float c_fCameraRotate; // Camera�� ȸ���� �ε巴�� ����
	const static float c_Degree; // Degree�� ��ȯ�ϴ� ���
private:
	static glm::vec3 vPosition; // ī�޶� ��ġ
	static glm::vec3 vFront; // ī�޶� ���� ����
	static glm::vec3 vRight; // ī�޶� ���� ����
	static glm::vec3 vUp; // ī�޶� ���� ����
public:
	static void Initialize(void); // ī�޶��� �ʱ� ��ġ�� ������ �����մϴ�
	static void Move(Direction direction, double deltaTime);
	static glm::mat4 getViewMatrix(void);
};
