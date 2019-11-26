//��� ������Ʈ(ī�޶�,���� �� ������Ʈ(����), ����Ʈ ��� �⺻ ������Ʈ�� ��� �޽��ϴ�.
#pragma once

enum class Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

struct Control_info {
	bool bRClick; // ���콺 ��Ŭ�� ����
	bool bLClick; // ���콺 ��Ŭ�� ����
	CPoint clickPoint; // ���콺�� �����ؼ� �̵��� �Ÿ�
	CPoint preClickPoint; // ���콺 �̵����� ���� �̵� ��ġ
};

class ObjectBase
{
protected:

public:
	ObjectBase();
	~ObjectBase();

	virtual void Initialize(struct Control_info* info) {};
	virtual void Move(Direction direction, double deltaTime, float scale = 1) { };
	virtual void Rotate(CPoint point, double deltaTime) {};
	//virtual void Scale(ObjectBase* obj) = 0;
};
