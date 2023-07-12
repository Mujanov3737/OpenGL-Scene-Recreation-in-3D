/*
 * Class for handling textures
 */
#include"TextureClass.h"

TextureClass::TextureClass(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	int widthImg, heightImg, channelsImg;		// Parameters for loading image file
	stbi_set_flip_vertically_on_load(true);		// Flip texture so that it does not load upside-down
	unsigned char* imgdata = stbi_load(image, &widthImg, &heightImg, &channelsImg, 0);  // Load in image file

	type = textureType; // Setting type of this class object to parameter type

	glGenTextures(1, &ID);		   // Create texture object
	glActiveTexture(slot);         // Set texture unit
	glBindTexture(type, ID);	   // Select texture, which is a 2D texture, rather than a 1D or 3D texture

	// Setting filter parameter to "nearest" (linear also works) (Texture type, setting to modify, and value of that setting)
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Setting wrap parameter to repeat texture
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Generating texture (RGBA for PNGs, RGB for JPGS)
	glTexImage2D(type, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, imgdata);
	glGenerateMipmap(type);		// Generating mipmaps of the texture when a smaller size is needed

	stbi_image_free(imgdata);		 // Release image data after texture is created
	glBindTexture(GL_TEXTURE_2D, 0); // De-select texture

}

void TextureClass::TextureUnit(ShaderClass& shader, const char* uniform, GLuint unit)
{
	GLuint textureUniform = glGetUniformLocation(shader.ID, uniform);    // Get uniform location
	glUniform1i(textureUniform, unit);	// Sets the value of the uniform
}

void TextureClass::Bind()
{
	glBindTexture(type, ID);
}

void TextureClass::Unbind()
{
	glBindTexture(type, 0);
}

void TextureClass::Delete()
{
	glDeleteTextures(1, &ID);
}