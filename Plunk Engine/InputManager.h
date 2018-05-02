#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

class Simulation;
struct GLFWwindow;
enum Camera_Movement;

class InputManager
{
public:
	InputManager();
	~InputManager();

	static Simulation* mSimulationInstance;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int, int, int, int);

	static const void MoveCamera(GLFWwindow* window, const Camera_Movement& pMovement);
	const void setInputCallbacks(GLFWwindow *const pWindow, Simulation* pSimulation);
private:
	static bool mFirstMouseMovement;
	static float mLastMouseX;
	static float mLastMouseY;
};	
#endif