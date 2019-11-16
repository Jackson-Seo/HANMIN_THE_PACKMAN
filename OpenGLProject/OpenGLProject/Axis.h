#ifndef AXIS_H
#define AXIS_H

class Axis {
private:
	// 정적 상수
	const static int c_iNumAxis; // 축의 개수
public:
	static void Draw(); // 배경이 되는 축을 그립니다.
};

#endif