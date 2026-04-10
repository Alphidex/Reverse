#pragma once

#include<glad/glad.h>

class EBO
{
public:
	EBO(const void* indices, GLsizeiptr size);
	~EBO();
	void bind() const;
	void unbind() const;
private:
	GLuint ID = 0;
};