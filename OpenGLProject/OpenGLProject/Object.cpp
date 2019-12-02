#include "pch.h"
#include "Object.h"

//오브젝트 초기 위치 초기화

void Object::initObjPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Object::setObjPos(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}

/*
	Object 객체 하나를 그립니다 그릴때 사용할 shader를 매개변수로 받습니다
	Object 객체 하나는 여러개의 Shape 구조체(shapes)와 여러개의 Texture 구조체(textures)로 이루어져 있습니다
	Shape 구조체 하나는 손가락 하나, 다리 하나처럼 Object에서 가장 작은 단위의 폴리곤 덩어리 입니다
	Texture 구조체는 대략 Texture 하나입니다
*/
void Object::Draw(const Shader& shader) {
	/*
		Object를 local 좌표계에서 world 좌표계로 변환하는 matrix를 계산합니다
		Identity 행렬부터 시작해서 Scale, Rotate, Translate를 적용합니다
		코드에서의 Translate, Rotate, Scale 순서와 실제 적용되는 순서는 반대입니다
		Scale -> Rotate -> Translate 순으로 적용됩니다
	*/

	glm::mat4 model = glm::mat4(1.0f); // Identitiy 행렬 설정
	model = glm::translate(model, glm::vec3(x, y, z)); // Translate
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0)); // Rotate
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f)); // Scale
	// 계산한 model matrix를 shader의 Uniform 변수로 넘겨줍니다
	shader.setMatrix4(model, "model");


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vaoId);

	// vector<Shape>로 되어있는 shapes에서 Shape 구조체 하나하나 그립니다
	for (auto it = this->shapes.begin(); it != this->shapes.end(); ++it)
	{
		/*
			if문 : 해당 Shape에 texture가 없나?
			TRUE : defaultColor에 색을 넣어서 fragment shader에 넘깁니다
			else if문 : 해당 Shape에 texture가 연결 되어있나?
				TRUE : 연결된 texture를 fragment shader에 넘깁니다
				FALSE : defaultColor에 색을 넣어서 fragment shader에 넘깁니다
		*/
		if (it->texname == "") {
			shader.setVec4(glm::vec4(1.0f), "defaultColor");
			// Object의 각 재질을 넘깁니다 저장된 재질이 없으므로 회색으로 넘깁니다
			shader.setVec3(glm::vec3(0.2f), "material.ambient");
			shader.setVec3(glm::vec3(0.2f), "material.diffuse");
			shader.setVec3(glm::vec3(0.2f), "material.specular");
			shader.setfloat(1.0f, "material.shininess");

			// Shape 구조체에 저장된대로 삼각형을 그립니다
			glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);
		}
		else if (this->textures[it->texname].textureId != -1) {
			// defaultColor를 무색으로 설정하여 texture가 적용되게 합니다
			shader.setVec4(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), "defaultColor");
			// Object의 각 재질을 넘깁니다
			shader.setVec3(this->textures[it->texname].ambient, "material.ambient");
			shader.setVec3(this->textures[it->texname].diffuse, "material.diffuse");
			shader.setVec3(this->textures[it->texname].specular, "material.specular");
			shader.setfloat(this->textures[it->texname].shininess, "material.shininess");

			// texture를 fragment shader에 넘깁니다
			glBindTexture(GL_TEXTURE_2D, this->textures[it->texname].textureId);
			shader.setUniform1i(0, "textureSampler");

			// Shape 구조체에 저장된대로 삼각형을 그립니다
			glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			// defaultColor를 흰색으로 설정하여 texture가 적용되지 않습니다
			shader.setVec4(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "defaultColor");
			// Object의 각 재질을 넘깁니다
			shader.setVec3(this->textures[it->texname].ambient, "material.ambient");
			shader.setVec3(this->textures[it->texname].diffuse, "material.diffuse");
			shader.setVec3(this->textures[it->texname].specular, "material.specular");
			shader.setfloat(this->textures[it->texname].shininess, "material.shininess");

			// Shape 구조체에 저장된대로 삼각형을 그립니다
			glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);
		}
	}
}

void Object::setScale(const float& xSc, const float& ySc, const float& zSc) {
	this->xSc = xSc;
	this->ySc = ySc;
	this->zSc = zSc;
}
void Object::setNumTriangles(const int& n) { m_iNumTriangles = n; }
void Object::setID(const GLuint& vao, const GLuint& vboV, const GLuint& vboUV) {
	vaoId = vao;
	vboVId = vboV;
	vboUvId = vboUV;
}