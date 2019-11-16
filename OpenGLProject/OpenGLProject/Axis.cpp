#include "pch.h"
#include "Axis.h"

// 정적변수 초기화
const int Axis::c_iNumAxis = 700;

// X축은 Red, Y축은 Green, Z축은 Blue로 축을 그린다
void Axis::Draw() {
	float x, y, z;
	glLineWidth(0.1);
	// 색상 트래킹 기능을 사용한다
	// 물체의 재질을 glColor로 지정한 색상을 사용한다
	// void glColorMaterial(GLenum face, GLenum mode)를 사용해서 어느 면에
	// 어느 조명을 적용할지 지정할 수 있다
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glBegin(GL_LINES);
	for (int i = 0; i < c_iNumAxis; i += 10) {
		glColor4f(100, 100, 100, 0.1);
		glVertex3f(c_iNumAxis / 2, 0, i - c_iNumAxis / 2);
		glVertex3f(-c_iNumAxis / 2, 0, i - c_iNumAxis / 2);
		glColor4f(100, 100, 100, 0.1);
		glVertex3f(i - c_iNumAxis / 2, 0, c_iNumAxis / 2);
		glVertex3f(i - c_iNumAxis / 2, 0, -c_iNumAxis / 2);
	}
	// X축
	glColor4f(255, 0, 0, 0.4);
	glVertex3f(c_iNumAxis / 2, 0, 0);
	glVertex3f(-c_iNumAxis / 2, 0, 0);
	// Y축
	glColor4f(0, 255, 0, 0.4);
	glVertex3f(0, c_iNumAxis / 2, 0);
	glVertex3f(0, -c_iNumAxis / 2, 0);
	// Z축
	glColor4f(0, 0, 255, 0.4);
	glVertex3f(0, 0, c_iNumAxis / 2);
	glVertex3f(0, 0, -c_iNumAxis / 2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
}