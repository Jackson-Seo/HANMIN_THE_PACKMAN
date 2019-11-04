#include "include/GL/glew.h"
#include "include/GL/glut.h"
#include "include/glm/glm.hpp"

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/freeglut.lib")

#include <iostream>
#include <fstream>
//using namespace std;
//
//// initial window size
//static int win_width = 300;
//static int win_height = 300;
//
//// rotation parameters
//static float xRot = 0.0f, dxRot = 1.0f;
//static float yRot = 0.0f, dyRot = 1.0f;
//static float zRot = 0.0f, dzRot = 1.0f;
//
//// A Shader program
//static GLuint programId = 0; // program ID
//static GLuint vsId = 0; // vertex shader ID
//static GLuint fsId = 0; // fragment shader ID
//const char* vsFile = "VertexShader.glsl"; // vertex shader file
//const char* fsFile = "FragmentShader.glsl"; // fragment shader file
//
//char* textFromFile(const char* filePathName, int& textLength)
//{
//	char* text = (char*)NULL;
//
//	// Open the file and move the current position to the end position of the file.
//	ifstream file(filePathName, ios::in | ios::ate);
//
//	if (file.fail())
//	{
//		cout << "Failed to open file: " << filePathName << endl;
//		return (char*)NULL;
//	}
//	else {
//		cout << "파일 열기에 성공" << endl;
//	}
//
//	textLength = file.tellg(); // the current position
//	text = new char[textLength + 1]; // memory allocation for storing text
//	file.seekg(0, ios::beg); // move to the start position of the file
//	file.read(text, textLength); // read data
//	file.close(); // close the file
//
//	if (text) { text[textLength] = '\0'; }
//	cout << text << endl;
//
//	return text;
//}
//
//void InitGL()
//{
//	GLenum status = glewInit();
//	if (status != GLEW_OK)
//	{
//		cout << glewGetErrorString(status) << endl;
//		exit(0);
//	}
//	cout << "OpenGL version: " << glGetString(GL_VERSION) << " supported." << endl;
//	cout << "GLEW version: " << glewGetString(GLEW_VERSION) << endl;
//}
//
//void InitShaders()
//{
//	///////////////////
//	// vertex shader //
//	{
//		// 1) Create a shader object.
//		vsId = glCreateShader(GL_VERTEX_SHADER);
//
//		// 2) Load a shader source code from a file.
//		int vsSrcLen = 0; // the length of the shader source code
//		const char* vsSrc = textFromFile(vsFile, vsSrcLen); // shader source code text
//		cout << "vsSrcLen : " << vsSrcLen << endl;
//
//		// 3) Specify the shader source code.
//		glShaderSource(vsId, 1, &vsSrc, &vsSrcLen);
//
//		// 4) Compile the shader.
//		glCompileShader(vsId);
//
//		// Check the compile status.
//		GLint status;
//		glGetShaderiv(vsId, GL_COMPILE_STATUS, &status);
//		if (status == GL_FALSE)
//		{
//			cout << "Failed to compile " << vsFile << endl;
//			int infoLogLen = 0;
//			glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &infoLogLen);
//			if (infoLogLen)
//			{
//				GLchar* infoLog = new GLchar[infoLogLen];
//				glGetShaderInfoLog(vsId, infoLogLen, &infoLogLen, infoLog);
//				cout << "Log: " << infoLog << endl;
//				delete[] infoLog;
//			}
//		}
//	}
//
//	/////////////////////
//	// fragment shader //
//	{
//		// 1) Create a shader object.
//		fsId = glCreateShader(GL_FRAGMENT_SHADER);
//
//		// 2) Load a shader source code from a file.
//		int fsSrcLen = 0; // the length of the shader source code
//		const char* fsSrc = textFromFile(fsFile, fsSrcLen); // shader source code text
//
//		// 3) Specify the shader source code.
//		glShaderSource(fsId, 1, &fsSrc, &fsSrcLen);
//
//		// 4) Compile the shader.
//		glCompileShader(fsId);
//
//		// Check the compile status.
//		GLint status;
//		glGetShaderiv(fsId, GL_COMPILE_STATUS, &status);
//		if (status == GL_FALSE)
//		{
//			cout << "Failed to compile " << fsFile << endl;
//			int infoLogLen = 0;
//			glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &infoLogLen);
//			if (infoLogLen)
//			{
//				GLchar* infoLog = new GLchar[infoLogLen];
//				glGetShaderInfoLog(vsId, infoLogLen, &infoLogLen, infoLog);
//				cout << "Log: " << infoLog << endl;
//				delete[] infoLog;
//			}
//		}
//	}
//
//	/////////////
//	// program //
//
//	// Create a program object to attach the shaders into.
//	programId = glCreateProgram();
//
//	// Attach the compiled shaders to the program object.
//	glAttachShader(programId, vsId);
//	glAttachShader(programId, fsId);
//
//	// Link the program object to the application.
//	glLinkProgram(programId);
//
//	// Disable the programmable processors so that the fixed functionality will be used.
//	glUseProgram(0);
//}
//
//void Display()
//{
//	// Set the color for the initialization, and reinitialize the color and the depth buffer with it.
//	glClearColor(0, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Turn on the depth test.
//	glEnable(GL_DEPTH_TEST);
//
//	// Viewport Transformation: Set the size of the photo. An then, print on it.
//	win_width = glutGet(GLUT_WINDOW_WIDTH);
//	win_height = glutGet(GLUT_WINDOW_HEIGHT);
//	glViewport(0, 0, win_width, win_height);
//
//	// Projection Transformation: Set the lens of the camera. And then, click the shutter of the camera.
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	const double fovy = 45.0; // The field of view angle, in degrees, in the y direction.
//	const double win_aspect = (double)win_width / (double)win_height; // The aspect ratio that determines the field of view in the x direction.
//	const double zNear = 0.1f; // The distance from the viewer to the near clipping plane.
//	const double zFar = 1000.0f; // The distance from the viewer to the far clipping plane.
//	gluPerspective(fovy, win_aspect, zNear, zFar);
//
//	// Viewing Transformation: Set the location and the direction of the camera.
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	// Modeling Transform: Locate objects and/or lights in the scene.
//	glTranslatef(0, 0, -5);
//	glRotatef(xRot = fmod(xRot + dyRot, 360.f), 1, 0, 0);
//	glRotatef(yRot = fmod(yRot + dyRot, 360.f), 0, 1, 0);
//	glRotatef(zRot = fmod(zRot + dyRot, 360.f), 0, 0, 1);
//
//	// Set the shader program.
//	glUseProgram(programId);
//
//	// Draw a teapot.
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // color: white
//	glutSolidTeapot(1); // size = 1
//
//	// Disable the programmable processors so that the fixed functionality will be used.
//	glUseProgram(0);
//
//	glFlush(); // To execute all commands in the command buffer sequentially.
//	glutSwapBuffers(); // To swap the back buffer fot the front buffer (double buffering).
//}
//
//void Keyboard(unsigned char ucKey, int x, int y)
//{
//	switch (ucKey)
//	{
//	case 27: { exit(0); } // 27: ESC
//	}
//}
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitWindowSize(win_width, win_height);
//	glutInitWindowPosition(200, 200);
//	glutCreateWindow("GLSL test");
//	glutDisplayFunc(Display);
//	glutKeyboardFunc(Keyboard);
//
//	InitGL();
//	InitShaders();
//
//	glutMainLoop();
//
//	return 0;
//}

using namespace std;

// initial window size
static int win_width = 300;
static int win_height = 300;

// rotation parameters
static float xRot = 0.0f, dxRot = 1.0f;
static float yRot = 0.0f, dyRot = 1.0f;
static float zRot = 0.0f, dzRot = 1.0f;

// A Shader program
static GLuint programId = 0; // program ID
static GLuint vsId = 0; // vertex shader ID
static GLuint fsId = 0; // fragment shader ID
const char* vsFile = "VertexShader.glsl"; // vertex shader file
const char* fsFile = "FragmentShader.glsl"; // fragment shader file

char* textFromFile(const char* filePathName, int& textLength)
{
	char* text = (char*)NULL;

	// Open the file and move the current position to the end position of the file.
	ifstream file(filePathName, ios::in | ios::ate);

	if (file.fail())
	{
		cout << "Failed to open file: " << filePathName << endl;
		return (char*)NULL;
	}

	textLength = file.tellg(); // the current position
	text = new char[textLength + 1]; // memory allocation for storing text
	file.seekg(0, ios::beg); // move to the start position of the file
	file.read(text, textLength); // read data
	file.close(); // close the file

	if (text) { text[textLength] = '\0'; }

	return text;
}

void InitGL()
{
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		cout << glewGetErrorString(status) << endl;
		exit(0);
	}
	cout << "OpenGL version: " << glGetString(GL_VERSION) << " supported." << endl;
	cout << "GLEW version: " << glewGetString(GLEW_VERSION) << endl;
}

void InitShaders()
{
	///////////////////
	// vertex shader //
	{
		// 1) Create a shader object.
		vsId = glCreateShader(GL_VERTEX_SHADER);

		// 2) Load a shader source code from a file.
		int vsSrcLen = 0; // the length of the shader source code
		const char* vsSrc = textFromFile(vsFile, vsSrcLen); // shader source code text

		// 3) Specify the shader source code.
		glShaderSource(vsId, 1, &vsSrc, &vsSrcLen);

		// 4) Compile the shader.
		glCompileShader(vsId);

		// Check the compile status.
		GLint status;
		glGetShaderiv(vsId, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			cout << "Failed to compile " << vsFile << endl;
			int infoLogLen = 0;
			glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &infoLogLen);
			if (infoLogLen)
			{
				GLchar* infoLog = new GLchar[infoLogLen];
				glGetShaderInfoLog(vsId, infoLogLen, &infoLogLen, infoLog);
				cout << "Log: " << infoLog << endl;
				delete[] infoLog;
			}
		}
	}

	/////////////////////
	// fragment shader //
	{
		// 1) Create a shader object.
		fsId = glCreateShader(GL_FRAGMENT_SHADER);

		// 2) Load a shader source code from a file.
		int fsSrcLen = 0; // the length of the shader source code
		const char* fsSrc = textFromFile(fsFile, fsSrcLen); // shader source code text

		// 3) Specify the shader source code.
		glShaderSource(fsId, 1, &fsSrc, &fsSrcLen);

		// 4) Compile the shader.
		glCompileShader(fsId);

		// Check the compile status.
		GLint status;
		glGetShaderiv(fsId, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			cout << "Failed to compile " << fsFile << endl;
			int infoLogLen = 0;
			glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &infoLogLen);
			if (infoLogLen)
			{
				GLchar* infoLog = new GLchar[infoLogLen];
				glGetShaderInfoLog(vsId, infoLogLen, &infoLogLen, infoLog);
				cout << "Log: " << infoLog << endl;
				delete[] infoLog;
			}
		}
	}

	/////////////
	// program //

	// Create a program object to attach the shaders into.
	programId = glCreateProgram();

	// Attach the compiled shaders to the program object.
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);

	// Link the program object to the application.
	glLinkProgram(programId);

	// Disable the programmable processors so that the fixed functionality will be used.
	glUseProgram(0);
}

void Display()
{
	// Set the color for the initialization, and reinitialize the color and the depth buffer with it.
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Turn on the depth test.
	glEnable(GL_DEPTH_TEST);

	// Viewport Transformation: Set the size of the photo. An then, print on it.
	win_width = glutGet(GLUT_WINDOW_WIDTH);
	win_height = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, win_width, win_height);

	// Projection Transformation: Set the lens of the camera. And then, click the shutter of the camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double fovy = 45.0; // The field of view angle, in degrees, in the y direction.
	const double win_aspect = (double)win_width / (double)win_height; // The aspect ratio that determines the field of view in the x direction.
	const double zNear = 0.1f; // The distance from the viewer to the near clipping plane.
	const double zFar = 1000.0f; // The distance from the viewer to the far clipping plane.
	gluPerspective(fovy, win_aspect, zNear, zFar);

	// Viewing Transformation: Set the location and the direction of the camera.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Modeling Transform: Locate objects and/or lights in the scene.
	glTranslatef(0, 0, -5);
	glRotatef(xRot = fmod(xRot + dyRot, 360.f), 1, 0, 0);
	glRotatef(yRot = fmod(yRot + dyRot, 360.f), 0, 1, 0);
	glRotatef(zRot = fmod(zRot + dyRot, 360.f), 0, 0, 1);

	// Set the shader program.
	glUseProgram(programId);

	// Draw a teapot.
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // color: white
	glutSolidTeapot(1); // size = 1

	// Disable the programmable processors so that the fixed functionality will be used.
	glUseProgram(0);

	glFlush(); // To execute all commands in the command buffer sequentially.
	glutSwapBuffers(); // To swap the back buffer fot the front buffer (double buffering).
}

void Keyboard(unsigned char ucKey, int x, int y)
{
	switch (ucKey)
	{
	case 27: { exit(0); } // 27: ESC
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("GLSL test");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	//glutIdleFunc(glutPostRedisplay);

	InitGL();
	InitShaders();

	glutMainLoop();

	return 0;
}