#include <stdio.h>

//在引用glad和glfw的头文件时，要先引用glad，再引用glfw，因为glfw中依赖了gl相关的东西，gl相关的东西是glad提供的
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include "MMGL/MMGL.hpp"

#define STRINGIZE(x)   #x
#define SHADER(shader) "" STRINGIZE(shader)

int main()
{
	printf("Hello OpenGL\n");
	glfwInit();

	//使用的opengl版本是3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

	//TODO:什么是CORE_PROFILE ，先跳过这个问题
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	int windowWidth = 1280;
	int windowHeight = 720;
	GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"MMOpenGL",NULL,NULL);

	//openGL运行模式 -- 单线程模式，如果想调用opengl的api，必须保证用同一个线程去调用
	//opengl不允许多个线程同时调用，通过glfwMakeContextCurrent让opengl的context -- 即window，和当前main函数的线程做一个绑定
	//一旦绑定成功之后，就只能在main函数所在的线程调用opengl
	glfwMakeContextCurrent(window);

	//初始化glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//char* shaderStr = (char*)"int main() {}";
	char* vertexShader = SHADER(
		#version 330\n

		layout(location = 0) in vec3 pos;

		out vec3 outPos;

		void main() {
			outPos = pos;
			gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
		}
	);
	printf("vertexShader:%s\n", vertexShader);

	char* fragmentShader = SHADER(
		#version 330\n

		out vec4 rgbaColor;

		in vec3 outPos;

		void main() {
			rgbaColor = vec4(outPos, 1.0);
	}
	);

	float vertex[] = {
		0.0f,	1.0f,	0.0f,
		-1.0f,	-1.0f,	0.0f,
		1.0f,	-1.0f,	0.0f
	};

	MMGLVAO* vao = new MMGLVAO();
	vao->AddVertex3D(vertex,3,0);

	//MMGLShader * shader = new MMGLShader(shaderStr,MMGLShaderType::MMGL_SHADER_VERTEX);
	MMGLProgram* program = new MMGLProgram(vertexShader, fragmentShader);

	//参数 GLenum type 有两种，顶点着色器 GL_VERTEX_SHADER 和 GL_FRAGMENT_SHADER
	/*GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader,1,&shaderStr,NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	GLint logLen = 0;//shader产生的日志的长度
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

	if (logLen > 0) { //长度大于0，存在log
		char* log = (char*)malloc(logLen);
		glGetShaderInfoLog(shader,logLen,NULL,log);

		printf("%s\n", log);

		free(log);
	}*/

	//GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);

	while (!glfwWindowShouldClose(window)) {
		//todo 绘制操作
		//在绘制之前要清空画布
		glClear(GL_COLOR_BUFFER_BIT);//把颜色相关的通道清除掉
		program->UseProgram();
		vao->BindVAO();

		glDrawArrays(GL_TRIANGLES,0,3);

		//todo 之后涉及到双缓冲再来讲glfwSwapBuffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete vao;
	//delete shader;
	delete program;

	//跳出循环后，释放掉glfw的资源
	glfwTerminate();
	
	return 0;
}
