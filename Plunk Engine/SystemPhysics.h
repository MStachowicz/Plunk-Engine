#ifndef SYSTEMPHYSICS_H
#define SYSTEMPHYSICS_H

#include "ISystem.h"
#include "IComponent.h"
#include "ComponentCollision.h"
#include "ComponentRigidBody.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <glm\glm.hpp>

//class ComponentRigidBody;

class SystemPhysics : public ISystem
{
public:
	SystemPhysics();
	~SystemPhysics();

	// Whether the gravity is being applied to all the rigid bodies
	bool applyGravity;
	// Whether the simulation is paused.
	bool pauseSimulation = false;


	void OnLoad(const std::shared_ptr<Entity> &entity);
	void OnTickStart();
	void OnTickStart(const std::shared_ptr<Entity> &entity);
	void Tick(const std::shared_ptr<Entity> &entity);

	void UpdateBodyPosition(glm::vec3 &pPosition, glm::vec3 &pVelocity, float tickDeltaTime);
	void UpdateBodyVelocity(glm::vec3 &pVelocity, glm::vec3 &resultantForce, const float &pMass, const float &tickDeltaTime);
	void ApplyGravity(glm::vec3 & pVelocity, const float &tickDeltaTime);
};
#endif