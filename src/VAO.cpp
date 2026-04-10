#include "header/VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	bind();
}

VAO::~VAO()
{
	if (ID != 0)
	{
		glDeleteVertexArrays(1, &ID);
		ID = 0;
	}
}

void VAO::linkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset)
{
	vbo.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void VAO::bind() const
{
	glBindVertexArray(ID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}
