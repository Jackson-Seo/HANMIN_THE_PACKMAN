#include "pch.h"
#include "Object.h"

//������Ʈ �ʱ� ��ġ �ʱ�ȭ

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
	Object ��ü �ϳ��� �׸��ϴ� �׸��� ����� shader�� �Ű������� �޽��ϴ�
	Object ��ü �ϳ��� �������� Shape ����ü(shapes)�� �������� Texture ����ü(textures)�� �̷���� �ֽ��ϴ�
	Shape ����ü �ϳ��� �հ��� �ϳ�, �ٸ� �ϳ�ó�� Object���� ���� ���� ������ ������ ��� �Դϴ�
	Texture ����ü�� �뷫 Texture �ϳ��Դϴ�
*/
void Object::Draw(const Shader& shader) {
	/*
		Object�� local ��ǥ�迡�� world ��ǥ��� ��ȯ�ϴ� matrix�� ����մϴ�
		Identity ��ĺ��� �����ؼ� Scale, Rotate, Translate�� �����մϴ�
		�ڵ忡���� Translate, Rotate, Scale ������ ���� ����Ǵ� ������ �ݴ��Դϴ�
		Scale -> Rotate -> Translate ������ ����˴ϴ�
	*/

	glm::mat4 model = glm::mat4(1.0f); // Identitiy ��� ����
	model = glm::translate(model, glm::vec3(x, y, z)); // Translate
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0)); // Rotate
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f)); // Scale
	// ����� model matrix�� shader�� Uniform ������ �Ѱ��ݴϴ�
	shader.setMatrix4(model, "model");


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vaoId);

	// vector<Shape>�� �Ǿ��ִ� shapes���� Shape ����ü �ϳ��ϳ� �׸��ϴ�
	for (auto it = this->shapes.begin(); it != this->shapes.end(); ++it)
	{
		/*
			if�� : �ش� Shape�� texture�� ����?
			TRUE : defaultColor�� ���� �־ fragment shader�� �ѱ�ϴ�
			else if�� : �ش� Shape�� texture�� ���� �Ǿ��ֳ�?
				TRUE : ����� texture�� fragment shader�� �ѱ�ϴ�
				FALSE : defaultColor�� ���� �־ fragment shader�� �ѱ�ϴ�
		*/
		if (it->texname == "") {
			shader.setVec4(glm::vec4(1.0f), "defaultColor");
			// Object�� �� ������ �ѱ�ϴ� ����� ������ �����Ƿ� ȸ������ �ѱ�ϴ�
			shader.setVec3(glm::vec3(0.2f), "material.ambient");
			shader.setVec3(glm::vec3(0.2f), "material.diffuse");
			shader.setVec3(glm::vec3(0.2f), "material.specular");
			shader.setfloat(1.0f, "material.shininess");

			// Shape ����ü�� ����ȴ�� �ﰢ���� �׸��ϴ�
			glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);
		}
		else if (this->textures[it->texname].textureId != -1) {
			// defaultColor�� �������� �����Ͽ� texture�� ����ǰ� �մϴ�
			shader.setVec4(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), "defaultColor");
			// Object�� �� ������ �ѱ�ϴ�
			shader.setVec3(this->textures[it->texname].ambient, "material.ambient");
			shader.setVec3(this->textures[it->texname].diffuse, "material.diffuse");
			shader.setVec3(this->textures[it->texname].specular, "material.specular");
			shader.setfloat(this->textures[it->texname].shininess, "material.shininess");

			// texture�� fragment shader�� �ѱ�ϴ�
			glBindTexture(GL_TEXTURE_2D, this->textures[it->texname].textureId);
			shader.setUniform1i(0, "textureSampler");

			// Shape ����ü�� ����ȴ�� �ﰢ���� �׸��ϴ�
			glDrawArrays(GL_TRIANGLES, it->idxBegin, it->cntVertex);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			// defaultColor�� ������� �����Ͽ� texture�� ������� �ʽ��ϴ�
			shader.setVec4(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "defaultColor");
			// Object�� �� ������ �ѱ�ϴ�
			shader.setVec3(this->textures[it->texname].ambient, "material.ambient");
			shader.setVec3(this->textures[it->texname].diffuse, "material.diffuse");
			shader.setVec3(this->textures[it->texname].specular, "material.specular");
			shader.setfloat(this->textures[it->texname].shininess, "material.shininess");

			// Shape ����ü�� ����ȴ�� �ﰢ���� �׸��ϴ�
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