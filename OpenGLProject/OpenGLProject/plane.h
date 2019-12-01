#pragma once
#include "Shader.h"

namespace DefaultPlane
{
	const float vertices[] = {
		// positions          // colors           // texture coords
		 1000.0f,  -50.0f, -1000.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1000.0f, -50.0f, 1000.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1000.0f, -50.0f, 1000.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1000.0f,  -50.0f, -1000.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	const unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	class plane
	{
	private:
		unsigned int VBO, VAO, EBO;
		unsigned int texture;

	public:

		void settingPlane(void);
		void caltranslate(const Shader& shader);
		void drawPlane(void);
	};

}
