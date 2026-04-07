#pragma once //pragma once是确保头文件只被引用一次

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

private:
	GLuint shader = 0;

};

