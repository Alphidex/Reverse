#ifndef VBO_H
#define VBO_H

#include<project/Optional.h>
#include<vector>
#include<glad/glad.h>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(void* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif