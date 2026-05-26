#include "MMGL.hpp"

MMGLVAO::MMGLVAO()
{
	glGenVertexArrays(1, &vao);
}

MMGLVAO::~MMGLVAO()
{
	//销毁VBO
	for (int i = 0;i < vboList.size();i++) {
		GLuint vbo = vboList[i];
		glDeleteBuffers(1, &vbo);
	}
	vboList.clear();

	if (ebo != 0) {
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}

	if (vao != NULL) {
		glDeleteVertexArrays(1, &vao);
		vao = NULL;
	}
}

int MMGLVAO::AddVertex3D(float* data, int vertexCount, int layout)//每调用一次AddVertex方法，就生成一个VBO
{
	glBindVertexArray(vao); //绑定vao

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//绑定vbo

	glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float),data,GL_STATIC_DRAW);
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(layout);

	vboList.push_back(vbo);

	glBindVertexArray(0);//解绑，就是把0号位绑定进来

	return 0;
}

int MMGLVAO::SetIndex(unsigned int* indexData, int indexCount)
{
	glBindVertexArray(vao); //绑定vao

	glGenBuffers(1,&ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData,GL_STATIC_DRAW);

	glBindVertexArray(0);//解绑，就是把0号位绑定进来

	drawTime = indexCount;

	return 0;
}

int MMGLVAO::BindVAO()
{
	glBindVertexArray(vao);
	return 0;
}

int MMGLVAO::Draw()
{
	BindVAO();
	glDrawElements(GL_TRIANGLES, drawTime,GL_UNSIGNED_INT,0);
	return 0;
}


