#include "pch.h"
#include "ObjectController.h"

// 정적변수 초기화
int ObjectController::s_iNumGenList = 0;

void ObjectController::LoadObject(const char* const fdir) {
	FILE* fp = nullptr;
	int read;
	char ch;
	GLfloat x, y, z;
	Object *obj;

	s_iNumGenList++;
	GLuint id = glGenLists(s_iNumGenList);
	obj = new Object(id);
	s_object.insert(std::make_pair(strrchr(fdir, '\\') + 1, *obj));
	fopen_s(&fp, fdir, "r");
	if (fp) {
		glPointSize(2.0);
		glNewList(id, GL_COMPILE);
		{
			glBegin(GL_POINTS);
			while (!(feof(fp))) {
				read = fscanf_s(fp, "%c %f %f %f", &ch, 1, &x, &y, &z);
				if (read == 4 && ch == 'v') {
					glVertex3f(x, y, z);
				}
			}
			glEnd();
		}
		glEndList();
		fclose(fp);
	}
}

void ObjectController::DrawObjects(void) {
	for (auto it = s_object.begin(); it != s_object.end(); it++) {
		it->second.Draw();
	}
}
