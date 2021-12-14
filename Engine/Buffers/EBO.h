#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

// Holds the EBO ID and performs all need actions

class EBO {
public:
	// Reference ID of the EBO
	GLuint ID;

	// Creates one EBO object with given indices and stores 
	// it's ID into class variable.
	// 
	// Receive the indices array and the size in bytes.
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif