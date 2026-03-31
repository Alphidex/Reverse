#include "header/VBO.h"

VBO::VBO(const void* vertices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	if (ID != 0)
	{
		glDeleteBuffers(1, &ID);
		ID = 0;
	}
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
