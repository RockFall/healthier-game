#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

// Holds the VBO ID and performs all need actions

class VBO {
public:
	// Reference ID of the VBO
	GLuint ID;

	// Creates one VBO object and stores 
	// it's ID into class variable.
	// 
	// Receive the vertices array and the size in bytes.
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif