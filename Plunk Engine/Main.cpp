// Main.cpp : Defines the entry point for the engine.

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputManager.h"
#include "WindowManager.h"

// Window properties
const GLint SCR_WIDTH = 1920, SCR_HEIGHT = 1080; // Screen dimensions.

int main()
{
	InputManager inputManager = InputManager();
	WindowManager windowManager = WindowManager(inputManager);
	GLFWwindow* window = windowManager.InitWindow();

	// Simulation loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Perform rendering here...

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}