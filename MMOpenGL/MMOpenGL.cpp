#include <stdio.h>

//在引用glad和glfw的头文件时，要先引用glad，再引用glfw，因为glfw中依赖了gl相关的东西，gl相关的东西是glad提供的
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	printf("Hello OpenGL");
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

	while (!glfwWindowShouldClose(window)) {
		//todo 绘制操作

		//todo 之后涉及到双缓冲再来讲glfwSwapBuffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//跳出循环后，释放掉glfw的资源
	glfwTerminate();
	
	return 0;
}
