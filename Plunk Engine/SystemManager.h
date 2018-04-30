#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "ISystem.h"
#include "EntityManager.h"
#include <vector>

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	std::vector<ISystem*> systemList;

	// Adds a system to the system list.
	void AddSystem(ISystem &system);
	// Calls every system OnLoad function to prepare the entities for the update/render cycle as well as the systems.
	void LoadSystems(EntityManager &manager, Simulation* pSimulation);
	// Calls every system action on every entity. Performs the actions if the mask of entity and system match.
	void ActionSystems(EntityManager &manager);
};

#endif