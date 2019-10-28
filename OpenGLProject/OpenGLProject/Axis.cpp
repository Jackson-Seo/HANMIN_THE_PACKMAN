#include "pch.h"
#include "Axis.h"

// �������� �ʱ�ȭ
const int Axis::c_iNumAxis = 700;

// X���� Red, Y���� Green, Z���� Blue�� ���� �׸���
void Axis::Draw() {
	float x, y, z;
	glLineWidth(0.1);
	// ���� Ʈ��ŷ ����� ����Ѵ�
	// ��ü�� ������ glColor�� ������ ������ ����Ѵ�
	// void glColorMaterial(GLenum face, GLenum mode)�� ����ؼ� ��� �鿡
	// ��� ������ �������� ������ �� �ִ�
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
	// X��
	glColor4f(255, 0, 0, 0.4);
	glVertex3f(c_iNumAxis / 2, 0, 0);
	glVertex3f(-c_iNumAxis / 2, 0, 0);
	// Y��
	glColor4f(0, 255, 0, 0.4);
	glVertex3f(0, c_iNumAxis / 2, 0);
	glVertex3f(0, -c_iNumAxis / 2, 0);
	// Z��
	glColor4f(0, 0, 255, 0.4);
	glVertex3f(0, 0, c_iNumAxis / 2);
	glVertex3f(0, 0, -c_iNumAxis / 2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
}