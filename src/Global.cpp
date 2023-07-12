#include "Global.h"


// Timing variables
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f;

// Variables for use in camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX;
float lastY;
bool firstMouse = true;
bool orthoEnabled = false;

void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// Function called when mouse wheel input is used
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Camera speed will increase when scrolling up and decrease when scrolling down
	camera.ProcessMouseScroll(yoffset, xoffset);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		return; // No negative edge
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		orthoEnabled = !orthoEnabled;
	}
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// ESC closes window
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		// W - Move camera forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		// S - Move camera backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		// A - Move camera left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		// D - Move camera right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)		// Q - Move camera up
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)		// E - Move camera down
		camera.ProcessKeyboard(DOWN, deltaTime);
	glfwSetKeyCallback(window, KeyCallback);				// P - Change perspective
}