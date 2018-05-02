#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

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
	Simulation(GLFWwindow *const window, const glm::vec3& pStartingPosition);
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

	double mSimulationTime; // Total amount of time simulation has been running.
	double mTimeScaling; // Amount to scale mDeltaTime by every frame.
	double mCurrentFrame; // Time the current frame started at.
	double mLastFrame; // Time the last frame started at.
	double mDeltaTime; // Amount of time between the current and last frame.
	double mRestitutionCoefficient; // Ratio of the final relative velocity after collision of bodies.

	void Run();
	void TogglePauseSimulation();
	void ChangeTimeScaling(double &pAmount);
	void ChangeRestitution(double &pAmount);

private:
	bool mSimulationPaused;
	double scrollWheelSensitivity; // The scale value when scrollwheel input is registered.
};
#endif