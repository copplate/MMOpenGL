#include "MMGL.hpp"

#include <stdlib.h>
#include <stdio.h>

MMGLShader::MMGLShader(char* shaderStr, MMGLShaderType type)//shaderStr是Shader的源代码
{
	if (type == MMGLShaderType::MMGL_SHADER_VERTEX) {
		//要让MMOpenGL里的shader的生命周期，和MMGLShader这个类里面对象的生命周期一致
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == MMGLShaderType::MMGL_SHADER_FRAGMENT) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else{
		shader = glCreateShader(GL_VERTEX_SHADER);
	}

	glShaderSource(shader,1,&shaderStr,NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	GLint logLen = 0;//shader产生的日志的长度
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

	if (logLen > 0) { //长度大于0，存在log
		char* log = (char*)malloc(logLen);
		glGetShaderInfoLog(shader, logLen, NULL, log);

		printf("%s\n", log);

		free(log);
	}
}
MMGLShader::~MMGLShader()
{
	if (shader != 0) {
		glDeleteShader(shader);
		shader = 0;
	}
}