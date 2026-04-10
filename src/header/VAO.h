#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	VAO();
	~VAO();

	// Define layout attributes
	void linkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset);
	void bind() const;
	void unbind() const;

private:
	GLuint ID = 0;
};
