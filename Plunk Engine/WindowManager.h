#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "InputManager.h"

class WindowManager
{
public:
	WindowManager(const InputManager& pInputManager);
	~WindowManager();

	GLFWwindow* const InitWindow();
	const bool ShouldWindowClose(GLFWwindow *const pWindow);

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	InputManager mInputManager; // Manager handling user input. Implements the Mouse, Keyboard and Scroll callbacks.
	GLFWwindow * mWindow; // Window used to draw to.
	const GLint SCR_WIDTH = 1920, SCR_HEIGHT = 1080; // Screen window dimensions.
};
#endif