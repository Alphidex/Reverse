#pragma once

#include<glad/glad.h>

class EBO
{
public:
	EBO(void* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
private:
	GLuint ID;
};