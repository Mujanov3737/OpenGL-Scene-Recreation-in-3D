/*
 * Class for handling parsing and creation of shaders
 */

#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderClass
{
	public:
		GLuint ID = 0;			// Shader ID
		GLuint lightID = 0;		// Shader ID for light

		struct ShaderProgramSrc		// Struct to hold parsed shader code
		{
			std::string VertexSource;
			std::string FragmentSource;
		};

		ShaderClass();

		void Activate();
		void Deactivate();
		void Delete();
		void ActivateLight();
		void DeactivateLight();
		void DeleteLight();
};

static ShaderClass::ShaderProgramSrc ParseShader(const std::string& path);
static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
static GLuint CompileShader(unsigned int type, const std::string& source);

#endif