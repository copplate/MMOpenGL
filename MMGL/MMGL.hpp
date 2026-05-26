#pragma once //pragma once是确保头文件只被引用一次

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

enum MMGLShaderType
{
	MMGL_SHADER_VERTEX = 1,
	MMGL_SHADER_FRAGMENT = 2
};


class MMGLShader
{
public:
	MMGLShader(char * shaderStr, MMGLShaderType type);//shaderStr是Shader的源代码
	~MMGLShader();

public:
	GLuint shader = 0;

};

class MMGLProgram
{
public:
	MMGLProgram(char * vertexShaderStr,char * fragmentShaderStr);
	~MMGLProgram();

	int UseProgram();
private:
	GLuint program = 0;
};

class MMGLVAO
{
public:
	MMGLVAO();
	~MMGLVAO();

	int AddVertex3D(float * data,int vertexCount,int layout);//每调用一次AddVertex方法，就生成一个VBO

	int SetIndex(unsigned int* indexData, int indexCount);

	int BindVAO();

	int Draw();

private:
	GLuint vao = 0;  // VAO的id
	GLuint ebo = 0;

	int drawTime = 0;

	std::vector<GLuint> vboList;
};

