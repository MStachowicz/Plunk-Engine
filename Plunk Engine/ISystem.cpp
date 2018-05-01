#include "ISystem.h"

ISystem::ISystem(std::string pName, IComponent::ComponentFlags MASK) : 
	name(pName), 
	MASK(MASK), 
	mSimulationInstance(nullptr),
	mRunning(true)
{}

ISystem::~ISystem() 
{}