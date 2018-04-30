#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager;
class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	GLFWwindow* const InitWindow();

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow * mWindow; // Window used to draw to.
	const GLint SCR_WIDTH = 1920, SCR_HEIGHT = 1080; // Screen window dimensions.
};
#endif