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

	Camera mCamera;

	float mCurrentFrame;
	float mLastFrame;
	float mDeltaTime;

	void Run();
};
#endif