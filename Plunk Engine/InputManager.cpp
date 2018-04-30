#include "InputManager.h"

InputManager::InputManager()
{}

InputManager::~InputManager()
{}

void InputManager::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
}

void InputManager::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}

void InputManager::key_callback(GLFWwindow* window, int, int, int, int)
{
	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
