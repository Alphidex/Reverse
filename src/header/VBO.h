#pragma once

#include<glad/glad.h>
#include<vector>

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(void* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint ID;
};
