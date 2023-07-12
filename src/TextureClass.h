/*
 * Class for handling textures
 */

#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

class TextureClass
{
	public:
		GLuint ID;  // Texture ID
		GLenum type;
		TextureClass(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

		void TextureUnit(ShaderClass &shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif