// Ahmet Mujanovic Project One

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "ShaderClass.h"
#include "TextureClass.h"
#include "Window.h"
#include "camera.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Global.h"

using std::cout; 
using std::endl;

// Vertices for cube and plane
GLfloat vertices[] = {

	// Triangle 1
   -0.5, -0.5, 0.0,		// index 0
	1.0, 0.0, 0.0,		// red
	0.0, 0.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

   -0.5, 0.5, 0.0,		// index 1
	0.0, 1.0, 0.0,		// green
	0.0, 1.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

	0.5, -0.5, 0.0,		// index 2	
	0.0, 0.0, 1.0,		// blue
	1.0, 0.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

	// Triangle 2	
	0.5, 0.5, 0.0,		// index 3	
	1.0, 0.0, 1.0,		// purple
	1.0, 1.0,			// UV
	0.0f, 0.0f, 1.0f    // Normal
};

// Vertices for cylinder
GLfloat verticesCyl[] = {
	// Triangle 1  (Top)
	0.0f, 0.0f, 0.0f,	// vert 1
	1.0f, 0.0f, 0.0f,	// red
	0.0, 1.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

	0.866f, 0.5f, 0.0f, // vert 2
	0.0f, 1.0f, 0.0f,	// green
	0.0, 0.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

	1.0f, 0.0f, 0.0f,	// vert 3
	0.0f, 0.0f, 1.0f,	// blue
	1.0, 0.0,			// UV
	0.0f, 0.0f, 1.0f,   // Normal

	// Triangle 2 (Top Right of Face)
	0.866f, 0.5f, 0.0f, // vert 4
	0.0f, 1.0f, 0.0f,	// green
	0.0, 0.0,			// UV  0 1,
	0.85f, 1.0f, 0.0f,  // Normal

	0.866f, 0.5f, -2.0f,// vert 5
	0.0f, 1.0f, 0.0f,	// green	
	1.0, 0.0,			// UV
	0.85f, 1.0f, 0.0f,  // Normal

	1.0f, 0.0f, 0.0f,	// vert 6
	0.0f, 0.0f, 1.0f,	// blue
	0.0, 1.0,			// UV
	0.85f, 1.0f, 0.0f,  // Normal

	// Triangle 3 (Bottom Left of Face)
	1.0f, 0.0f, 0.0f,	// vert 7
	0.0f, 0.0f, 1.0f,	// blue
	0.0, 1.0,			// UV
	0.85f, 1.0f, 0.0f,  // Normal

	1.0f, 0.0f, -2.0f,	// vert 8
	0.0f, 0.0f, 1.0f,	// blue
	0.0,  0.0,			// UV
	0.85f, 1.0f, 0.0f,  // Normal

	0.866f, 0.5f, -2.0f,// vert 9
	0.0f, 1.0f, 0.0f,	// green
	1.0, 0.0,			// UV
	0.85f, 1.0f, 0.0f,  // Normal

	// Triangle 4 (Bottom)
	0.0f, 0.0f, -2.0f,	// vert 1
	1.0f, 0.0f, 0.0f,	// red
	0.0, 1.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal

	0.866f, 0.5f, -2.0f, // vert 2
	0.0f, 1.0f, 0.0f,	// green
	0.0, 0.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal

	1.0f, 0.0f, -2.0f,	// vert 3
	0.0f, 0.0f, 1.0f,	// blue
	1.0, 0.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal
};

// Vertices for tapered blade plane
GLfloat verticesBlade[] = {

	// Triangle 1
   -0.19, -0.19, 0.0,		// index 0
	1.0, 0.0, 0.0,		// red
	0.0, 0.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal

   -0.35, 1.5, 0.0,		// index 1
	0.0, 1.0, 0.0,		// green
	0.0, 1.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal

	0.19, -0.19, 0.0,		// index 2	
	0.0, 0.0, 1.0,		// blue
	1.0, 0.0,			// UV
	0.0f, 0.0f, -1.0f,   // Normal

	0.35, 1.5, 0.0,		// index 3	
	1.0, 0.0, 1.0,		// purple
	1.0, 1.0,			// UV
	0.0f, 0.0f, -1.0f    // Normal
};


// Vertices for the light source. Will only contain position attributes
GLfloat verticesLightSrc[] = {
	-0.5, -0.5,  0.0,
	-0.5,  0.5,  0.0,
	 0.5, -0.5,  0.0,
	 0.5,  0.5,  0.0
};

// Define element indices
GLuint indices[] = {
	0, 1, 2,
	1, 2, 3
};

// Plane Transforms
glm::vec3 planePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.5f),
	glm::vec3(0.5f,  0.0f,  0.0f),
	glm::vec3(0.0f,  0.0f,  -0.5f),
	glm::vec3(-0.5f, 0.0f,  0.0f),
	glm::vec3(0.0f, 0.5f,  0.0f),
	glm::vec3(0.0f, -0.5f,  0.0f)
};

// Array storing transformations to create cylinder and cube to save on vertex memory
glm::float32 planeRotations[] = { 0.0f, 90.0f, 180.0f, -90.0f, -90.f, 90.f };
//glm::float32 triRotations[] = { 0.0f, 60.0f, 120.0f, 180.0f, 240.0f, 300.0f };
glm::float32 triRotations[] = { 0.0f, 30.0f, 60.0f, 90.0f, 120.0f, 150.0f, 180.0f, 210.0f, 240.0f, 270.0f, 300.0f, 330.0f };


// Object color
glm::vec3 objectColor(1.0f, 0.2f, 0.0f);

// Main light position and color
glm::vec3 lightPosition(20.0f, 7.5f, 5.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

// Seconday light position and color
glm::vec3 lightPositionSec(-20.0f, 7.5f, 5.0f);
glm::vec3 lightColorSec(0.99f, 0.81f, 0.80f);	// Low warm red light

// Scale of light object
glm::vec3 lightScale(0.25f, 0.25f, 0.25f);

// Lamp animation bool
bool isLampOrbiting = true;

int main()
{
	Window windowObj = Window();  // Constructor will load libraries, create a window object, and set the render viewport

	lastX = windowObj.WINDOW_WIDTH / 2.0f;
	lastY = windowObj.WINDOW_HEIGHT / 2.0f;

	// Functions to specify what to do for each mouse event
	glfwSetCursorPosCallback(windowObj._window, MousePositionCallback);
	glfwSetScrollCallback(windowObj._window, MouseScrollCallback);

	// Enabling mouse capture
	glfwSetInputMode(windowObj._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	ShaderClass shaderObj = ShaderClass();		// Creating shader class object and calling constructor to compile and create shaders

	// Creating VAO, VBO, and EBO for the Cube
	VAO vaoCube;
	vaoCube.Bind();
	VBO vboCube = VBO(vertices, sizeof(vertices));
	EBO eboCube = EBO(indices, sizeof(indices));
	vaoCube.LinkAttribute(vboCube, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		// Describing and sending position attribute data for vertices vbo
	vaoCube.LinkAttribute(vboCube, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));		// Describing and sending color attribute data
	vaoCube.LinkAttribute(vboCube, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));		// Describing and sending texture attribute data
	vaoCube.LinkAttribute(vboCube, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));		// Describing and sending normal attribute data
	vaoCube.Unbind();
	vboCube.Unbind();
	eboCube.Unbind();
	// END CUBE

	// Creating VAO and VBO for the Cylinder
	VAO vaoCyl;
	vaoCyl.Bind();
	VBO vboCyl = VBO(verticesCyl, sizeof(verticesCyl));
	vaoCyl.LinkAttribute(vboCyl, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		// Describing and sending position attribute data for vertices vbo
	vaoCyl.LinkAttribute(vboCyl, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));		// Describing and sending color attribute data
	vaoCyl.LinkAttribute(vboCyl, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));		// Describing and sending texture attribute data
	vaoCyl.LinkAttribute(vboCyl, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));		// Describing and sending normal attribute data
	vaoCyl.Unbind();
	vboCyl.Unbind();
	// END CYLINDER

	// Creating VAO and VBO for the Blade
	VAO vaoBlade;
	vaoBlade.Bind();
	VBO vboBlade = VBO(verticesBlade, sizeof(verticesBlade));
	EBO eboBlade = EBO(indices, sizeof(indices));
	vaoBlade.LinkAttribute(vboBlade, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		// Describing and sending position attribute data for vertices vbo
	vaoBlade.LinkAttribute(vboBlade, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));		// Describing and sending color attribute data
	vaoBlade.LinkAttribute(vboBlade, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));		// Describing and sending texture attribute data
	vaoBlade.LinkAttribute(vboBlade, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));		// Describing and sending normal attribute data
	vaoBlade.Unbind();
	vboBlade.Unbind();
	eboBlade.Unbind();
	// END BLADE

	// Creating VAO, VBO, and EBO for the Plane
	VAO vaoFloor;
	vaoFloor.Bind();
	VBO vboFloor = VBO(vertices, sizeof(vertices));
	EBO eboFloor = EBO(indices, sizeof(indices));
	vaoFloor.LinkAttribute(vboFloor, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);		// Describing and sending position attribute data for vertices vbo
	vaoFloor.LinkAttribute(vboFloor, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));		// Describing and sending color attribute data
	vaoFloor.LinkAttribute(vboFloor, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));		// Describing and sending texture attribute data
	vaoFloor.LinkAttribute(vboFloor, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));		// Describing and sending normal attribute data
	vaoFloor.Unbind();
	vboFloor.Unbind();
	eboFloor.Unbind();
	// END PLANE

	// Creating VAO, VBO and EBO for main light source cube
	VAO vaoLightSrc;
	vaoLightSrc.Bind();
	VBO vboLightSrc = VBO(verticesLightSrc, sizeof(verticesLightSrc));
	EBO eboLightSrc = EBO(indices, sizeof(indices));
	vaoLightSrc.LinkAttribute(vboLightSrc, 0, 3, GL_FLOAT, 0 * sizeof(float), (void*)0); // Only need to link positional data
	vboLightSrc.Unbind();
	eboLightSrc.Unbind();
	// END LIGHT SRC CUBE

	// Creating VAO, VBO and EBO for secondary light source cube
	VAO vaoLightSrcSec;
	vaoLightSrcSec.Bind();
	VBO vboLightSrcSec = VBO(verticesLightSrc, sizeof(verticesLightSrc));
	EBO eboLightSrcSec = EBO(indices, sizeof(indices));
	vaoLightSrcSec.LinkAttribute(vboLightSrcSec, 0, 3, GL_FLOAT, 0 * sizeof(float), (void*)0);  // Only need to link positional data
	vboLightSrcSec.Unbind();
	eboLightSrcSec.Unbind();
	// End of secondary light source cube buffer assignment

	// Calling texture class to load image and create a texture object to assign for each texture needed in the render. Using tex0 slot.
	TextureClass tamside = TextureClass("res/textures/tamside.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tamside.TextureUnit(shaderObj, "tex0", 0);		// Side of bottle
	TextureClass tamtop = TextureClass("res/textures/tamtop.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tamtop.TextureUnit(shaderObj, "tex0", 0);		// Top and bottom of bottle
	TextureClass tamcap = TextureClass("res/textures/tamcap.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tamcap.TextureUnit(shaderObj, "tex0", 0);		// Cap of bottle
	TextureClass jar = TextureClass("res/textures/jar.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	jar.TextureUnit(shaderObj, "tex0", 0);		// Jar base
	TextureClass blkbmpy = TextureClass("res/textures/blkbmpy.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	blkbmpy.TextureUnit(shaderObj, "tex0", 0);		// Black bumpy texture for jar cap and scraper
	TextureClass metalscr = TextureClass("res/textures/metalscr.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	metalscr.TextureUnit(shaderObj, "tex0", 0);		// Metal texture for blade
	TextureClass wood = TextureClass("res/textures/wood.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	wood.TextureUnit(shaderObj, "tex0", 0);			// Plane texture

	// Rubik's Cube textures
	TextureClass ruBlue = TextureClass("res/textures/ruBlue.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruBlue.TextureUnit(shaderObj, "tex0", 0);
	TextureClass ruGreen = TextureClass("res/textures/ruGreen.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruGreen.TextureUnit(shaderObj, "tex0", 0);
	TextureClass ruOrange = TextureClass("res/textures/ruOrange.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruOrange.TextureUnit(shaderObj, "tex0", 0);
	TextureClass ruRed = TextureClass("res/textures/ruRed.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruRed.TextureUnit(shaderObj, "tex0", 0);
	TextureClass ruWhite = TextureClass("res/textures/ruWhite.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruWhite.TextureUnit(shaderObj, "tex0", 0);
	TextureClass ruYellow = TextureClass("res/textures/ruYellow.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	ruYellow.TextureUnit(shaderObj, "tex0", 0);

	// Main render loop
	while (!glfwWindowShouldClose(windowObj._window))
	{
		//Calculating orbit for primary light
		const float angularVelocity = glm::radians(45.0f);
		if (isLampOrbiting)
		{
			glm::vec4 newPosition = glm::rotate(angularVelocity * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(lightPosition, 1.0);
			lightPosition.x = newPosition.x;
			lightPosition.y = newPosition.y;
			lightPosition.z = newPosition.z;

			glm::vec4 newPositionSec = glm::rotate(angularVelocity * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(lightPositionSec, 1.0);
			lightPositionSec.x = newPositionSec.x;
			lightPositionSec.y = newPositionSec.y;
			lightPositionSec.z = newPositionSec.z;
		}

		// Handling frame timing
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(windowObj._window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Set buffer color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Apply buffer color

		glEnable(GL_DEPTH_TEST);						// Enable z-depth. This will allow for pixels closer to the camera to be colored first, giving the illusion of depth
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Enabling Wireframe mode
		glDepthFunc(GL_LEQUAL);							// Used with Depth test

		shaderObj.Activate();	// Activating main shader program for light and the pyramid

		// Retrieves and passes transform matrices to the Shader program
		GLint modelLoc = glGetUniformLocation(shaderObj.ID, "model");
		GLint viewLoc = glGetUniformLocation(shaderObj.ID, "view");
		GLint projLoc = glGetUniformLocation(shaderObj.ID, "projection");

		// Get light and object color/position location
		GLint objectColorLoc = glGetUniformLocation(shaderObj.ID, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(shaderObj.ID, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(shaderObj.ID, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(shaderObj.ID, "viewPos");

		// Get light color/position location for the secondary light
		GLint lightColorLocSec = glGetUniformLocation(shaderObj.ID, "lightColorSec");
		GLint lightPosLocSec = glGetUniformLocation(shaderObj.ID, "lightPosSec");

		// Model Matrix
		glm::mat4 model = glm::mat4(1.0f);		// Initializing model identity matrix

		// View Matrix
		glm::mat4 view = camera.GetViewMatrix();

		// Projection Matrix
		glm::mat4 projection;
		if (!orthoEnabled)	// The "P" key will switch between perspective and orthographic projection
			projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)(windowObj.WINDOW_WIDTH / windowObj.WINDOW_HEIGHT), 0.1f, 100.0f);
		else if (orthoEnabled)
			projection = glm::ortho(-5.0f, 5.0f, -5.0f, (GLfloat)(windowObj.WINDOW_WIDTH / windowObj.WINDOW_HEIGHT), 0.1f, 100.0f);

		// Assigning MVP locations
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);		// Assign Colors
		glUniform3f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b);			// Assign Light Color
		glUniform3f(lightPosLoc, lightPosition.x, lightPosition.y, lightPosition.z);	// Assign Light Position
		glUniform3f(lightColorLocSec, lightColorSec.r, lightColorSec.g, lightColorSec.b);			// Assign secondary Light Color
		glUniform3f(lightPosLocSec, lightPositionSec.x, lightPositionSec.y, lightPositionSec.z);	// Assign secondary Light Position
		const glm::vec3 cameraPosition = camera.Position;
		glUniform3f(viewPosLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);	// Pass camera position

		// BEGIN CUBE TEXTURE BIND AND DRAW
		vaoCube.Bind();			// Select vertex array buffer
		eboCube.Bind();
		tamside.Bind();			// Select texture buffer
		// Drawing Base of Cement
		for (GLuint i = 0; i < 6; i++) // Transform planes to form cube
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, planePositions[i]);
			model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i >= 4)
			{
				tamside.Unbind();
				tamtop.Bind();
				model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		tamtop.Unbind();
		// Drawing Rubik's cube
		ruRed.Bind();
		for (GLuint i = 0; i < 6; i++) // Transform planes to form cube
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.225f, 0.25f));
			model = glm::scale(model, glm::vec3(1.45f, 1.45f, 1.45f));	// Scale the strip to the proper size
			model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, planePositions[i]);
			model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i == 1)
			{
				ruRed.Unbind();
				ruYellow.Bind();
			}
			if (i == 2)
			{
				ruYellow.Unbind();
				ruOrange.Bind();
			}
			if (i == 3)
			{
				ruOrange.Unbind();
				ruWhite.Bind();
			}
			if (i >= 4)
			{
				if (i == 4)
				{
					ruWhite.Unbind();
					ruBlue.Bind();
				}
				if (i == 5)
				{
					ruBlue.Unbind();
					ruGreen.Bind();
				}
				model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		ruRed.Unbind();
		// Drawing scraper attachment point
		blkbmpy.Bind();
		for (GLuint i = 0; i < 6; i++) // Transform planes to form cube
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::translate(glm::mat4(1.0f), glm::vec3(2.52f, -0.25f, -0.55f));
			model = glm::scale(model, glm::vec3(0.45f, 0.15f, 0.45f));	// Scale the strip to the proper size
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, planePositions[i]);
			model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i >= 4)
			{
				model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		blkbmpy.Unbind();
		vaoCube.Unbind();
		eboCube.Unbind();
		// END CUBE TEXTURE BIND AND DRAW

		// BEGIN BLADE TEXTURE BIND AND DRAW
		metalscr.Bind();
		vaoBlade.Bind();
		vboBlade.Bind();
		eboBlade.Bind();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.25f, -0.25f, -0.28f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		metalscr.Unbind();
		vaoBlade.Unbind();
		vboBlade.Unbind();
		eboBlade.Unbind();
		// END BLADE TEXTURE BIND AND DRAW

		// BEGIN CYLINDER TEXTURE BIND AND DRAW
		vaoCyl.Bind();			// Select vertex array buffer
		tamcap.Bind();			// Select texture buffer

		// Drawing top of cap
		for (int i = 0; i < 12; i++)	// Transforming triangles to form cylinder
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));	// Scale the strip to the proper size
			model = glm::translate(model, glm::vec3(0.0f, 3.42f, 0.0f));		 // Raise position of strip to be above the cube
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(triRotations[i]), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate strip on z by increments in array
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 9);	// Draw cylinder on screen
		}
		tamcap.Unbind();
		jar.Bind();
		// Drawing base of jar
		for (int i = 0; i < 12; i++)	// Transforming triangles to form cylinder
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));	// Scale the strip to the proper size
			model = glm::translate(model, glm::vec3(1.7f, 1.32f, -2.5f));		 // Raise position of strip to be above the cube
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(triRotations[i]), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate strip on z by increments in array
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 9);	// Draw cylinder on screen
		}
		jar.Unbind();
		blkbmpy.Bind();
		// Drawing cap of jar
		for (int i = 0; i < 12; i++)	// Transforming triangles to form cylinder
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::scale(model, glm::vec3(0.73f, 0.25f, 0.73f));	// Scale the strip to the proper size
			model = glm::translate(model, glm::vec3(1.75f, 5.75f, -2.57f));		 // Raise position of strip to be above the cube
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate strip into proper position
			model = glm::rotate(model, glm::radians(triRotations[i]), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate strip on z by increments in array
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 9);	// Draw cylinder on screen
		}
		// Drawing scraper handle
		for (int i = 0; i < 12; i++)	// Transforming triangles to form cylinder
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // Rotate strip into proper position
			model = glm::scale(model, glm::vec3(0.4f, 0.25f, 0.65f));	// Scale the strip to the proper size
			model = glm::translate(model, glm::vec3(3.5f, -1.0f, -3.5f));		 // Raise position of strip to be above the cube
			model = glm::rotate(model, glm::radians(triRotations[i]), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate strip on z by increments in array
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 12);	// Draw cylinder on screen, using all vertices to create a complete cylinder
		}
		blkbmpy.Unbind();
		vaoCyl.Unbind();
		// END CYLINDER TEXTURE BIND AND DRAW

		// BEGIN PLANE TEXTURE BIND AND DRAW
		vaoFloor.Bind();
		eboFloor.Bind();
		wood.Bind();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.f, -0.5f, 0.f));
		model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.f, 6.f, 6.f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		vaoFloor.Unbind();
		eboFloor.Unbind();
		wood.Unbind();
		// END PLANE TEXTURE BIND AND DRAW

		shaderObj.Deactivate(); // Stop using shader program for objects

		// START PRIMARY LIGHT SOURCE DRAW
		shaderObj.ActivateLight();  // Begin user shader program cubes
		// Retrieves and passes transform matrices to the Shader program for the light
		GLint modelLocLight = glGetUniformLocation(shaderObj.lightID, "model");
		GLint viewLocLight = glGetUniformLocation(shaderObj.lightID, "view");
		GLint projLocLight = glGetUniformLocation(shaderObj.lightID, "projection");
		glUniformMatrix4fv(viewLocLight, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocLight, 1, GL_FALSE, glm::value_ptr(projection));
		vaoLightSrc.Bind();	 // Bind vao for light source cube
		eboLightSrc.Bind();	 // Bind ebo for light source cube
		for (GLuint i = 0; i < 6; i++)  // Transform planes to form cube
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::scale(model, lightScale);
			model = glm::translate(model, planePositions[i] + lightPosition);
			model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i >= 4)
				model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLocLight, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		vaoLightSrc.Unbind();	 // Bind vao for light source cube
		eboLightSrc.Unbind();	 // Bind ebo for light source cube

		vaoLightSrcSec.Bind();	 // Bind vao for light source cube
		eboLightSrcSec.Bind();	 // Bind ebo for light source cube

		// Transform planes to form cube
		for (GLuint i = 0; i < 6; i++)
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Position strip at 0,0,0
			model = glm::scale(model, lightScale);
			model = glm::translate(model, planePositions[i] + lightPositionSec);
			model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i >= 4)
				model = glm::rotate(model, glm::radians(planeRotations[i]), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLocLight, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}

		vaoLightSrcSec.Unbind();
		eboLightSrcSec.Unbind();
		// END SECONDARY LIGHT SOURCE DRAW

		shaderObj.DeactivateLight();  // Stop using shader for cubes

		glfwSwapBuffers(windowObj._window);		// Swap set back buffer with front buffer

		glfwPollEvents(); // Allows for events related to window to be processed
	}

	// Release objects from memory
	vaoCube.Delete();
	vboCube.Delete();
	eboCube.Delete();
	vaoLightSrc.Delete();
	vboLightSrc.Delete();
	eboLightSrc.Delete();
	vaoLightSrcSec.Delete();
	vboLightSrcSec.Delete();
	eboLightSrcSec.Delete();
	vaoFloor.Delete();
	vboFloor.Delete();
	eboFloor.Delete();
	vaoCyl.Delete();
	vboCyl.Delete();

	tamside.Delete();
	tamtop.Delete();
	tamcap.Delete();
	wood.Delete();

	shaderObj.Delete();
	shaderObj.DeleteLight();

	// Displays GPU OpenGL version
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glfwTerminate();

	return 0;
}