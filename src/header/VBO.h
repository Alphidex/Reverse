#pragma once

#include<glad/glad.h>
#include<vector>

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(const void* vertices, GLsizeiptr size);
	~VBO();

	void bind() const;
	void unbind() const;

private:
	GLuint ID = 0;
};
