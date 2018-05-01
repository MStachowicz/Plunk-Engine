// Abstract base class defining a system which will carry out actions on entities.
#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <string>
#include "Entity.h"

class Simulation;

class ISystem
{

public:
	ISystem(std::string pName, IComponent::ComponentFlags MASK);
	virtual ~ISystem();

	std::string name;
	const IComponent::ComponentFlags MASK;
	Simulation* mSimulationInstance;
	bool mRunning; // Whether this system is being called in the simulation loop.

	virtual void OnLoad(const std::shared_ptr<Entity> &entity) = 0;
	
	// These methods are called in the following order every frame.

	virtual void OnTickStart(const std::shared_ptr<Entity> &entity) = 0;
	virtual void OnTickStart() = 0;
	virtual void Tick(const std::shared_ptr<Entity> &entity) = 0;
};
#endif