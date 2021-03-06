// Main.cpp : Defines the entry point for the engine.

#include "WindowManager.h"
#include "Simulation.h"

class GLFWwindow;

int main()
{
	WindowManager windowManager = WindowManager();
	GLFWwindow* window = windowManager.InitWindow();

	Simulation kerplunk = Simulation(window, glm::vec3(0.f, 1.0001f, 5.f));

	// Simulation loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		kerplunk.Run();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}