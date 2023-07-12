/*
 * Class for handling library initialization and window creation
 */

#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
	public:
		const char* WINDOW_NAME = "AHMET_PROJECT_ONE";
		const unsigned int WINDOW_HEIGHT = 800;
		const unsigned int WINDOW_WIDTH = 800;
		GLFWwindow* _window;

		int Initialize();
		void SelectWindow();
		void SetRenderArea();
		Window();
};

#endif
