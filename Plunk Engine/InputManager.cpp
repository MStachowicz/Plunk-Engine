#include "InputManager.h"
#include "Simulation.h"

InputManager::InputManager()
{}

InputManager::~InputManager()
{}

Simulation* InputManager::mSimulationInstance = nullptr;
bool InputManager::mFirstMouseMovement = true;

float InputManager::mLastMouseX = 0.f;
float InputManager::mLastMouseY = 0.f;

void InputManager::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (mFirstMouseMovement)
	{
		mLastMouseX = xpos;
		mLastMouseY = ypos;
		InputManager::mFirstMouseMovement = false;
	}

	float xoffset = xpos - mLastMouseX;
	float yoffset = mLastMouseY - ypos; // reversed since y-coordinates go from bottom to top

	mLastMouseX = xpos;
	mLastMouseY = ypos;

	mSimulationInstance->mCamera.ProcessMouseMovement(xoffset, yoffset);
}

void InputManager::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	mSimulationInstance->ChangeTimeScaling(yoffset);
	//mSimulationInstance->mCamera.ProcessMouseScroll(yoffset);
}

void InputManager::key_callback(GLFWwindow* window, int, int, int, int)
{
	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
		
	// CAMERA MOVEMENT
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(FORWARD, mSimulationInstance->mDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(BACKWARD, mSimulationInstance->mDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(LEFT, mSimulationInstance->mDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(RIGHT, mSimulationInstance->mDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(UP, mSimulationInstance->mDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		mSimulationInstance->mCamera.ProcessKeyboard(DOWN, mSimulationInstance->mDeltaTime);

	// Pause simulation
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		mSimulationInstance->TogglePauseSimulation();
}

const void InputManager::setInputCallbacks(GLFWwindow *const pWindow, Simulation* pSimulation)
{
	mSimulationInstance = pSimulation;

	glfwSetCursorPosCallback(pWindow, mouse_callback);
	glfwSetScrollCallback(pWindow, scroll_callback);
	glfwSetKeyCallback(pWindow, key_callback);
}
