#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include <memory>

class Simulation;

class InputManager
{
public:
	InputManager();
	~InputManager();

	Simulation* mSimulationInstance;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int, int, int, int);

	const void setInputCallbacks(GLFWwindow *const pWindow);
};
#endif