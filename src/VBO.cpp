/*
 * Class for handling vertex buffer objects
 */

#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// Creating buffer for vertices
	glGenBuffers(1, &ID);
	// Make this buffer the current object so it can be used (GL_ARRAY is one of many types of buffers)
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Send vertex data to the buffer object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	// Make this buffer the current object so it can be used (GL_ARRAY is one of many types of buffers)
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	// Release the current buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}