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
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		mSimulationInstance->ChangeTimeScaling(yoffset);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		mSimulationInstance->mCamera.ProcessMouseScroll(yoffset);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		mSimulationInstance->ChangeRestitution(yoffset);
	}
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
		MoveCamera(window, FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MoveCamera(window, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MoveCamera(window, LEFT); 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MoveCamera(window, RIGHT);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		MoveCamera(window, UP); 
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		MoveCamera(window, DOWN);

	// Pause simulation
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		mSimulationInstance->TogglePauseSimulation();
}

const void InputManager::MoveCamera(GLFWwindow* window, const Camera_Movement& pMovement)
{
	// Removes the time scaling being applied to the simulation to not affect camera movement.
	double deltaTime = mSimulationInstance->mDeltaTime / mSimulationInstance->mTimeScaling;
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		deltaTime *= 5;

		switch (pMovement)
		{
		case Camera_Movement::FORWARD:
			mSimulationInstance->mCamera.ProcessKeyboard(FORWARD, deltaTime);
			break;
		case Camera_Movement::BACKWARD:
			mSimulationInstance->mCamera.ProcessKeyboard(BACKWARD, deltaTime);
			break;
		case Camera_Movement::LEFT:
			mSimulationInstance->mCamera.ProcessKeyboard(LEFT, deltaTime);
			break;
		case Camera_Movement::RIGHT:
			mSimulationInstance->mCamera.ProcessKeyboard(RIGHT, deltaTime);
			break;
		case Camera_Movement::UP:
			mSimulationInstance->mCamera.ProcessKeyboard(UP, deltaTime);
			break;
		case Camera_Movement::DOWN:
			mSimulationInstance->mCamera.ProcessKeyboard(DOWN, deltaTime);
			break;
		}
}

const void InputManager::setInputCallbacks(GLFWwindow *const pWindow, Simulation* pSimulation)
{
	mSimulationInstance = pSimulation;

	glfwSetCursorPosCallback(pWindow, mouse_callback);
	glfwSetScrollCallback(pWindow, scroll_callback);
	glfwSetKeyCallback(pWindow, key_callback);
}
