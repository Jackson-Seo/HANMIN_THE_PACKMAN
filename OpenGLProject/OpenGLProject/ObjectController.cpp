#include "pch.h"
#include "ObjectController.h"

#pragma once
#define TINYOBJLOADER_IMPLEMENTATION
#include "include/tinyobjloader/tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

// 정적변수 초기화
std::map<std::string, Object> ObjectController::s_object = {};
int ObjectController::s_iNumGenList = 0;

/*
	.obj파일을 불러서 map인 s_object에 저장합니다
	파일명은 따로 map의 key로 저장하고 파싱한 .obj파일은 Object 객체에 저장해 value로 사용합니다
*/
void ObjectController::LoadObject(const Shader& const shader, const char* const fdir) {
	TRACE1("\n%s를 불러옵니다...\n", fdir);
	Object obj;
	GLuint vao, vboV, vboUV, vboVN;
	int numTriangles = 0;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn; // 경고 메시지 입니다
	std::string err; // 에러 메시지 입니다

	std::string filename(fdir); // 파일의 경로입니다
	std::string base_dir = ""; // 파일이 존재하는 폴더의 경로입니다
	if (filename.find_last_of("/\\") != std::string::npos)
		base_dir += filename.substr(0, filename.find_last_of("/\\")) + "/";
	else
		base_dir += '.' + '/';

	// load obj file
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fdir, base_dir.c_str());

	// load Texture Images from materials
	for (auto m = 0; m < materials.size(); m++)
	{
		tinyobj::material_t* mp = &materials[m];
		if (mp->diffuse_texname == "") {
			continue;
		}

		if (obj.textures.find(mp->diffuse_texname) == obj.textures.end()) {
			Object::Texture t;
			std::string texture_filename = mp->diffuse_texname;
			texture_filename = base_dir + mp->diffuse_texname; // need check valid

			t.image = stbi_load(texture_filename.c_str(), &t.w, &t.h, &t.comp, STBI_default);

			// Texture VBO를 만듭니다
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &t.textureId);
			glBindTexture(GL_TEXTURE_2D, t.textureId);
			if (t.comp == 3) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.w, t.h, 0, GL_RGB, GL_UNSIGNED_BYTE, t.image);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (t.comp == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.w, t.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.image);
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			// Texture 확대 축소 필터
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			obj.textures.insert(std::make_pair(mp->diffuse_texname, t));
			stbi_image_free(t.image);
		}
	}
	TRACE0("\nmaterials 파싱이 끝났습니다\n");

	// load obj position, uv, normal from shapes
	Object::Shape sp;
	sp.idxBegin = 0;
	sp.cntVertex = 0;
	sp.texname = "";

	for (auto s = 0; s < shapes.size(); s++)
	{
		int current_material_id = 0;
		if (materials.size() > 0)
		{
			current_material_id = shapes[s].mesh.material_ids[0];
			if (current_material_id >= 0) {
				sp.texname = materials[current_material_id].diffuse_texname;
			}
		}

		for (auto f = 0; f < shapes[s].mesh.indices.size() / 3; f++)
		{
			tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
			tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
			tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

			// v = vertex = bufferPosition
			// Vertex 받아온다
			glm::vec3 v[3];
			for (int k = 0; k < 3; k++)
			{
				int f0 = idx0.vertex_index;
				int f1 = idx1.vertex_index;
				int f2 = idx2.vertex_index;

				v[0][k] = attrib.vertices[3 * f0 + k];
				v[1][k] = attrib.vertices[3 * f1 + k];
				v[2][k] = attrib.vertices[3 * f2 + k];
			}

			// vt = tc = uv = bufferUV
			// 텍스쳐 좌표 받아온다
			glm::vec2 tc[3];
			if (attrib.texcoords.size() > 0) {
				if ((idx0.texcoord_index < 0) || (idx1.texcoord_index < 0) ||
					(idx2.texcoord_index < 0)) {
					// face does not contain valid uv index.
					tc[0][0] = 0.0f;
					tc[0][1] = 0.0f;
					tc[1][0] = 0.0f;
					tc[1][1] = 0.0f;
					tc[2][0] = 0.0f;
					tc[2][1] = 0.0f;
				}
				else
				{
					// Flip Y coord.
					tc[0][0] = attrib.texcoords[2 * idx0.texcoord_index];
					tc[0][1] = 1.0f - attrib.texcoords[2 * idx0.texcoord_index + 1];
					tc[1][0] = attrib.texcoords[2 * idx1.texcoord_index];
					tc[1][1] = 1.0f - attrib.texcoords[2 * idx1.texcoord_index + 1];
					tc[2][0] = attrib.texcoords[2 * idx2.texcoord_index];
					tc[2][1] = 1.0f - attrib.texcoords[2 * idx2.texcoord_index + 1];
				}
			}
			else {
				tc[0][0] = 0.0f;
				tc[0][1] = 0.0f;
				tc[1][0] = 0.0f;
				tc[1][1] = 0.0f;
				tc[2][0] = 0.0f;
				tc[2][1] = 0.0f;
			}

			// vn = vertex normal = bufferNomal
			// 노말 Vertex 받아온다
			glm::vec3 n[3];
			bool invalid_normal_index = false;
			int nf0 = idx0.normal_index;
			int nf1 = idx1.normal_index;
			int nf2 = idx2.normal_index;
			if (attrib.normals.size() > 0)
			{
				if ((nf0 < 0) || (nf1 < 0) || (nf2 < 0))
				{
					// normal index is missing from this face.
					invalid_normal_index = true;
				}
				else
				{
					for (int k = 0; k < 3; k++)
					{
						n[0][k] = attrib.normals[3 * nf0 + k];
						n[1][k] = attrib.normals[3 * nf1 + k];
						n[2][k] = attrib.normals[3 * nf2 + k];
					}
				}
			}
			else
			{
				CalcNormal(n[0], v[0], v[1], v[2]);
				n[1][0] = n[0][0];
				n[1][1] = n[0][1];
				n[1][2] = n[0][2];
				n[2][0] = n[0][0];
				n[2][1] = n[0][1];
				n[2][2] = n[0][2];
			}

			// save to Object
			for (int k = 0; k < 3; k++)
			{
				// push buffer
				obj.bufferPosition.push_back(v[k]);
				obj.bufferUV.push_back(tc[k]);
				obj.bufferNormal.push_back(n[k]);
				numTriangles++;
			}

			// shape마다 생성한다
			int material_id = shapes[s].mesh.material_ids[f];
			if (current_material_id == material_id)
			{
				sp.cntVertex += 3;
			}
			else
			{
				obj.shapes.push_back(sp);
				if (materials.size() > 0 && material_id >= 0)
				{
					sp.texname = materials[material_id].diffuse_texname;
				}
				else {
					sp.texname = "";
				}
				sp.idxBegin += sp.cntVertex;
				sp.cntVertex = 3;
				current_material_id = material_id;
			}
		}
		obj.shapes.push_back(sp);
	}
	TRACE0("\nshapes 파싱이 끝났습니다\n");
	// VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position
	glGenBuffers(1, &vboV);
	glBindBuffer(GL_ARRAY_BUFFER, vboV);
	glBufferData(GL_ARRAY_BUFFER, obj.bufferPosition.size() * sizeof(glm::vec3), &obj.bufferPosition[0], GL_STATIC_DRAW);
	// Program 객체로부터 이름이 vertexPosition인 속성 변수가 바인딩된 인덱스를 리턴받아서 저장합니다
	GLint vertexPosition = glGetAttribLocation(shader.getID(), "vertexPosition");
	// vertexPosition에 저장된 인덱스가 가리키는 vertexPosition 속성이 VBO에서 어떻게 데이터를 가져올 수 있는지 지정해줍니다
	glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Vertex Shader의 position 속성과 VBO의 position 데이터간의 연결이 동작하기 위해서는 glEnableVertexAttribArray 함수를 사용하여 vertexPosition을 활성화해야 합니다
	glEnableVertexAttribArray(vertexPosition);

	// UV
	glGenBuffers(1, &vboUV);
	glBindBuffer(GL_ARRAY_BUFFER, vboUV);
	glBufferData(GL_ARRAY_BUFFER, obj.bufferUV.size() * sizeof(glm::vec2), &obj.bufferUV[0], GL_STATIC_DRAW);
	GLint vertexUV = glGetAttribLocation(shader.getID(), "vertexUV"); // VertexShader에서 vertexUV의 인덱스
	glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexUV); // vertexUV 활성화

	// Normal 벡터 추가

	// obj를 삽입한다
	obj.setNumTriangles(numTriangles);
	obj.setID(vao, vboV, vboUV);
	s_object.insert(std::make_pair(strrchr(fdir, '/') + 1, obj));
}

// Key에 해당하는 Object 객체를 찾아서 반환합니다 구현만해놓고 사용하고있진 않습니다
Object ObjectController::FindObject(const std::string key) {
	return s_object.find(key)->second;
}

// map에 저장된 Object를 하나하나 그립니다
void ObjectController::DrawObjects(const Shader& shader) {
	for (auto it = s_object.begin(); it != s_object.end(); it++) {
		it->second.Draw(shader);
	}
}

// LoadObject 함수에서 호출되는 함수입니다 노말 벡터를 계산합니다
void ObjectController::CalcNormal(glm::vec3 N, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
	float v10[3];
	v10[0] = v1[0] - v0[0];
	v10[1] = v1[1] - v0[1];
	v10[2] = v1[2] - v0[2];

	float v20[3];
	v20[0] = v2[0] - v0[0];
	v20[1] = v2[1] - v0[1];
	v20[2] = v2[2] - v0[2];

	N[0] = v20[1] * v10[2] - v20[2] * v10[1];
	N[1] = v20[2] * v10[0] - v20[0] * v10[2];
	N[2] = v20[0] * v10[1] - v20[1] * v10[0];

	float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
	if (len2 > 0.0f)
	{
		float len = sqrtf(len2);

		N[0] /= len;
		N[1] /= len;
		N[2] /= len;
	}
}