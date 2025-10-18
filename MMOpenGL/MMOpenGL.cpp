#include <stdio.h>

//在引用glad和glfw的头文件时，要先引用glad，再引用glfw，因为glfw中依赖了gl相关的东西，gl相关的东西是glad提供的
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	printf("Hello OpenGL");
	return 0;
}
