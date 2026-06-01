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

		uniform float a;

		layout(location = 0) in vec3 pos;
		layout(location = 1) in vec3 uvPos;


		out vec3 outPos;
		out vec3 outUVPos;

		void main() {
			outPos = pos;
			outUVPos = uvPos;

			float _a = sin(a);
			_a = 1.0;

			gl_Position = vec4(pos.x * _a, pos.y * _a, pos.z * _a, 1.0);
		}
	);
	printf("vertexShader:%s\n", vertexShader);

	char* fragmentShader = SHADER(
		#version 330\n

		out vec4 rgbaColor;

		in vec3 outPos;
		in vec3 outUVPos;

		uniform sampler2D t;//纹理

		void main() 
		{
			//纹理坐标
			vec2 uv = vec2(outUVPos.x, outUVPos.y);
			vec4 color = texture(t,uv);
			// rgbaColor = vec4(outPos, 1.0);

			rgbaColor = color;
		}
	);

	float vertex[] = {
		-1.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,
		1.0f,	-1.0f,	0.0f,
		-1.0f,	-1.0f,	0.0f,
	};

	float vertexUV[] = {
		0.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,
		1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	0.0f,
	};

	unsigned int index[] = {
		0,3,1,
		1,3,2
	};

	MMGLVAO* vao = new MMGLVAO();
	vao->AddVertex3D(vertex,4,0);
	vao->AddVertex3D(vertexUV, 4, 1);
	vao->SetIndex(index,6);

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


	//RGB  RGB
	//RGB  RGB
	int imgWidth = 2;
	int imgHeight = 2;
	unsigned char imgData[] = {
		255,0,0,             0,255,0,
		0,0,255,             127,127,127
	};

	GLuint textureId = 0;
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D,textureId);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, imgWidth, imgHeight,0,GL_RGB,GL_UNSIGNED_BYTE, imgData);


	float aa = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		//todo 绘制操作
		//在绘制之前要清空画布
		glClear(GL_COLOR_BUFFER_BIT);//把颜色相关的通道清除掉
		program->UseProgram();

		GLuint loc = glGetUniformLocation(program->program,"a");
		glUniform1f(loc, aa);

		GLuint textureLoc = glGetUniformLocation(program->program,"t");
		//激活0号纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(textureLoc,0);//0是纹理单元的编号，opengl有32个纹理单元，opengl es有16个纹理单元

		vao->Draw();

		aa += 0.03;

		//glDrawArrays(GL_TRIANGLES,0,6);

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
