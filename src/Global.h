#ifndef GLOBAL_H
#define GLOBAL_H

#include "camera.h"
#include <GLFW/glfw3.h>

// Timing variables
extern float deltaTime;		// Time between current frame and last frame
extern float lastFrame;

// Variables for use in camera
extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;
extern bool orthoEnabled;

// Declaring functions to handle input
extern void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
extern void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
extern void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);	// Key press function
extern void ProcessInput(GLFWwindow* window);

#endif
