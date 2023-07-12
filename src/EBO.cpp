#include "EBO.h"
/*
 * Class for handling element buffer objects
 */

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// Creating buffer for indices
	glGenBuffers(1, &ID);
	// Make this buffer the current object so it can be used
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Send vertex data to the buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	// Make this buffer the current object so it can be used
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	// Release the current buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}