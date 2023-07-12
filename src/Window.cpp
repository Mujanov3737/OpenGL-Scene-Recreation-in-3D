/*
 * Class for handling library initialization and window creation
 */

#include "Window.h"

int Window::Initialize()
{
	// Calling function to intialize GLFW library
	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	// Giving GLFW a "hint" in order to specify what version of OpenGL is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Giving "hint" in order to specify which OpenGL package profile to use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Calling window creation class to set window object parameters
	_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);

	// Conditional check for a failure to create window
	if (_window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set the window as the current window to render
	glfwMakeContextCurrent(_window);

	// Calling function for GLAD to load proper pointer functions for drivers
	if (!gladLoadGL()) {
		std::cout << "Failed to load GLAD" << std::endl;
		return EXIT_FAILURE;
	};
}

void Window::SelectWindow()
{
	// Set the window as the current window to render
	glfwMakeContextCurrent(_window);
}

void Window::SetRenderArea()
{
	// Setting render area
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Window::Window()
{
	Initialize();
	SetRenderArea();
}
