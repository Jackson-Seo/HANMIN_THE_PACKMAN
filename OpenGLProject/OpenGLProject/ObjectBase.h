//모든 오브젝트(카메라,월드 상 오브젝트(액터), 라이트 모두 기본 오브젝트를 상속 받습니다.
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
	bool bRClick; // 마우스 우클릭 감지
	bool bLClick; // 마우스 좌클릭 감지
	CPoint clickPoint; // 마우스가 누적해서 이동한 거리
	CPoint preClickPoint; // 마우스 이동에서 이전 이동 위치
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
