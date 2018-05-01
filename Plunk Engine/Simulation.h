#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Entity.h"
#include "EntityManager.h"

#include "InputManager.h"
#include "WindowManager.h"

#include "SystemManager.h"
#include "SystemPhysics.h"
#include "SystemRender.h"
#include "SystemLighting.h"
#include "SystemCollision.h"
#include "SystemShadows.h"

class Simulation
{
public:
	Simulation(GLFWwindow *const window);
	~Simulation();

	EntityManager entityManager;
	InputManager inputManager;
	SystemManager systemManager;

	SystemPhysics systemPhysics;
	SystemCollision systemCollision;
	SystemShadows systemShadows;
	SystemLighting systemLighting;
	SystemRender systemRender;

	Camera mCamera; // Camera used to navigate the simulation.

	float mSimulationTime; // Total amount of time simulation has been running.
	float mTimeScaling; // Amount to scale mDeltaTime by every frame.
	float mCurrentFrame; // Time the current frame started at.
	float mLastFrame; // Time the last frame started at.
	float mDeltaTime; // Amount of time between the current and last frame.

	void Run();
};
#endif