#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	
    EBO(void* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif