#include "pch.h"
#include "ObjectController.h"

// 정적변수 초기화
std::map<std::string, Object> ObjectController::s_object = {};
int ObjectController::s_iNumGenList = 0;

void ObjectController::LoadObject(const char* const fdir) {
	Object obj;
	GLuint vao, vboV, vboUV;
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

		if (obj.textures.find(mp->diffuse_texname) == obj.textures.end()) {
			Object::Texture t;
			std::string texture_filename = mp->diffuse_texname;
			texture_filename = base_dir + mp->diffuse_texname; // need check valid

			t.image = stbi_load(texture_filename.c_str(), &t.w, &t.h, &t.comp, STBI_default);

			obj.textures.insert(std::make_pair(mp->diffuse_texname, t));
		}
	}

	// load obj position, uv, normal from shapes
	Object::SubMesh sm;
	sm.idxBegin = 0;
	sm.cntVertex = 0;
	sm.textureId = 0;
	sm.texname = "";

	for (size_t s = 0; s < shapes.size(); s++)
	{
		int current_material_id = 0;
		if (materials.size() > 0)
		{
			current_material_id = shapes[s].mesh.material_ids[0];
			sm.texname = materials[current_material_id].diffuse_texname;
		}

		for (size_t f = 0; f < shapes[s].mesh.indices.size() / 3; f++)
		{
			tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
			tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
			tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

			// v = vertex = bufferPosition
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
					assert(attrib.texcoords.size() >
						size_t(2 * idx0.texcoord_index + 1));
					assert(attrib.texcoords.size() >
						size_t(2 * idx1.texcoord_index + 1));
					assert(attrib.texcoords.size() >
						size_t(2 * idx2.texcoord_index + 1));

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
						assert(size_t(3 * nf0 + k) < attrib.normals.size());
						assert(size_t(3 * nf1 + k) < attrib.normals.size());
						assert(size_t(3 * nf2 + k) < attrib.normals.size());
						n[0][k] = attrib.normals[3 * nf0 + k];
						n[1][k] = attrib.normals[3 * nf1 + k];
						n[2][k] = attrib.normals[3 * nf2 + k];
					}
				}
			}
			else
			{
				invalid_normal_index = true;
			}
			if (invalid_normal_index) {
				// compute geometric normal
				CalcNormal(n[0], v[0], v[1], v[2]);
				n[1][0] = n[0][0];
				n[1][1] = n[0][1];
				n[1][2] = n[0][2];
				n[2][0] = n[0][0];
				n[2][1] = n[0][1];
				n[2][2] = n[0][2];
			}

			// save to DrawObject
			for (int k = 0; k < 3; k++)
			{
				// push buffer
				obj.bufferPosition.push_back(v[k]);
				obj.bufferUV.push_back(tc[k]);
				obj.bufferNormal.push_back(n[k]);
				numTriangles++;
			}

			// Make SubSet
			int material_id = shapes[s].mesh.material_ids[f];
			if (current_material_id == material_id)
			{
				sm.cntVertex += 3;
			}
			else
			{
				obj.subMeshs.push_back(sm);

				if (materials.size() > 0)
				{
					sm.texname = materials[material_id].diffuse_texname;
				}
				sm.idxBegin += sm.cntVertex;
				sm.cntVertex = 3;

				current_material_id = material_id;
			}
		}

		// Texture VBO
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &sm.textureId);
		glBindTexture(GL_TEXTURE_2D, sm.textureId);
		if (obj.textures[sm.texname].comp == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, obj.textures[sm.texname].w, obj.textures[sm.texname].h, 0, GL_RGB,
				GL_UNSIGNED_BYTE, obj.textures[sm.texname].image);
		}
		else if (obj.textures[sm.texname].comp == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, obj.textures[sm.texname].w, obj.textures[sm.texname].h, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, obj.textures[sm.texname].image);
		}
		else {
			assert(0);  // TODO
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		obj.subMeshs.push_back(sm);
	}
	// VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position
	glGenBuffers(1, &vboV);
	glBindBuffer(GL_ARRAY_BUFFER, vboV);
	glBufferData(GL_ARRAY_BUFFER, obj.bufferPosition.size() * sizeof(glm::vec3), &obj.bufferPosition[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// UV
	glGenBuffers(1, &vboUV);
	glBindBuffer(GL_ARRAY_BUFFER, vboUV);
	glBufferData(GL_ARRAY_BUFFER, obj.bufferUV.size() * sizeof(glm::vec2), &obj.bufferUV[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Normal 벡터 추가

	// obj를 삽입한다
	obj.setNumTriangles(numTriangles);
	obj.setID(vao, vboV, vboUV);
	s_object.insert(std::make_pair(strrchr(fdir, '/') + 1, obj));

	/*--------------------------------------------------------------------------------------------------------------
	---------------------------------------------Create VBO---------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------

	for (int i = 0; i < obj.subMeshs.size(); i++)
	{
		Object::SubMesh* sm = &obj.subMeshs[i];

		if (sm->textureId == 0 && sm->texname != "")
		{
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &sm->textureId);
			glBindTexture(GL_TEXTURE_2D, sm->textureId);
			if (obj.textures[sm->texname].comp == 3) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, obj.textures[sm->texname].w, obj.textures[sm->texname].h, 0, GL_RGB,
					GL_UNSIGNED_BYTE, obj.textures[sm->texname].image);
			}
			else if (obj.textures[sm->texname].comp == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, obj.textures[sm->texname].w, obj.textures[sm->texname].h, 0, GL_RGBA,
					GL_UNSIGNED_BYTE, obj.textures[sm->texname].image);
			}
			else {
				assert(0);  // TODO
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	// VAO
	glGenVertexArrays(1, obj->vaoId);
	glBindVertexArray(o->vaoId);

	// Position
	glGenBuffers(1, &o->vboVId);
	glBindBuffer(GL_ARRAY_BUFFER, o->vboVId);
	glBufferData(GL_ARRAY_BUFFER, o->bufferPosition.size() * sizeof(glm::vec3), &o->bufferPosition[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// UV
	glGenBuffers(1, &o->vboUvId);
	glBindBuffer(GL_ARRAY_BUFFER, o->vboUvId);
	glBufferData(GL_ARRAY_BUFFER, o->bufferUV.size() * sizeof(glm::vec2), &o->bufferUV[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Normal 벡터 추가
	*/
}

Object ObjectController::FindObject(const std::string key) {
	return s_object.find(key)->second;
}

void ObjectController::DrawObjects(void) {
	for (auto it = s_object.begin(); it != s_object.end(); it++) {
		it->second.Draw();
	}
}

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
