/*
 * Class for handling vertex array objects
 */

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
		GLuint ID;  // VAO ID
		VAO();

		void LinkAttribute(VBO VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};

#endif
