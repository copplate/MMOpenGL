
#cmake_minimum_required (VERSION 3.8)

#写一个搜索路径
include_directories(../3rdpart/glfw/include/)
include_directories(../3rdpart/glad/include/)

link_directories(../3rdpart/glfw/lib)

add_library (
		MMGL 
		#../3rdpart/glad/src/glad.c #把源码直接拿过来编译，函数都在这个.c文件里实现，这样就能找到所有函数
		 MMGL.hpp
		 
		  "MMGLShader.cpp" "MMGLProgram.cpp" "MMGLVAO.cpp")


