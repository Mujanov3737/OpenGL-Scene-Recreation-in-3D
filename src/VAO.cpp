/*
 * Class for handling vertex array objects
 */

#include "VAO.h"

// Constructor call for creating an array object to store pointers to multiple buffers
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Associate a VBO with this VAO. This will also unbind the VBO
// Offset is the memory distance to the next attribute, stride is memory distance to the next vertex
void VAO::LinkAttribute(VBO VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	// Select vertex array
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	// Unbind vertex array
	glBindVertexArray(0);
}

void VAO::Delete()
{
	// Release VAO from memory
	glDeleteVertexArrays(1, &ID);
}