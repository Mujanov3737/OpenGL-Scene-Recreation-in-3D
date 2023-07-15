# 3D Graphics w/ OpenGL
This repository contains a visual studio solution that builds a 3D scene using C++, the OpenGL specification, and the many libraries like GLFW, GLAD, and glm used to implement OpenGL. The 3D scene was created from a 2D reference image taken by myself. While not an ideal recreation, please note this scene was created to explore and exercise knowledge on OpenGL through a coding environment, rather than a 3D graphics suite tool like Blender.

If you choose to build the project yourself or run the executable that has been compiled already, you can control the scene as follows:
* A and D keys to strafe the camera left and right
* E and Q keys to strafe the camera up and down
* W and S keys to move forward and backwards
* Mouse scroll wheel to adjust the speed of the camera movement
* Mouse cursor to look around the scene
* P key to toggle the perspective from perspective to orthographic projection
  
# Project Demo
![anim5](https://github.com/Mujanov3737/OpenGL-Scene-Recreation-in-3D/assets/75598761/d01a70a3-eab5-43c9-9b52-ed7af61921b9)
# Reference Image
![refimage](https://github.com/Mujanov3737/OpenGL-Scene-Recreation-in-3D/assets/75598761/046e9d0e-5039-42d6-980b-cfe5f9290f54)
# General Thoughts on Computer Graphics/Project
## Designing
This project was among the more complicated I have attempted to tackle, particularly due to the fact that there is a wealth of knowledge needed to create a working program using the OpenGL specification. The discipline of computer graphics is a vast one that could easily require complete dedication and specialization in order to master. As such, designing the application took some extra thought and care. Referring to the documentation provided by the various OpenGL libraries used provided an excellent starting point when deciding what was required to begin making calls to the graphics card or establishing a basic foundation of a window and viewport. On a broader note, studying the many primitives used in creating 3D scenes and coming up with a scene to model myself was really the first starting point in the design process. It is often a mistake to get directly stuck into the programming environment and playing around with the code. But knowing the long-term goal of what the final product is intended to be, in addition to familiarizing myself with more of the theoretical concepts of 3D graphics and the OpenGL specification, were all crucial in a smoother development phase.
## Developing
As mentioned previously, the documentation for the many libraries used in the OpenGL specification provide an excellent starting point for the code. GLFW offers some boiler plate code to get started with loading the library and creating the window while the loading libraries like GLEW and GLAD offer robust documentation on initializing the pointers to the graphics drivers and other utilities. The development process was fairly straightforward and included two "phases" of sorts. Initially, the learning process of how each concept worked entailed reading the nature of the concept such as the vertices, shaders, transformations, textures, camera. After reading, a basic form of these concepts were coded into the application with help from the respective documentation. Once the desired result was achieving and the concepts were understood, the next “phase” was a matter of refactoring the code so that it was modular and easier to use. This generally involved packing away the functionality into separate classes or storing shader code into a text file to be parsed, rather than in the main source file.
## Lessons Learned
This course gave me a significant number of takeaways, both in terms of computer graphics and programming in general. I had made a few breakthroughs using more advanced C++ concepts that I had played around with over the course of the project like the "intern" and "extern" modifier and how translation units functioned in C++. Even if I do not pursue a career in computer graphics, learning how to design a more complicated application while first understanding advanced concepts is a crucial stepping stone in being a professional developer.
Additionally, having a foundational understand of the technologies that go into doing something as seemingly simple as drawing things on a screen is exciting. Often, the focus is on abstraction far away from the hardware, but being as close as working with pointer functions that point to drivers the graphics card uses gives a deep insight as to how many layers of abstraction there really are in the field of computer science.
