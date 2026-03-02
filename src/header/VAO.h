#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	VAO();

	// Define layout attributes
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete();

private:
	GLuint ID;
};
