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

	void OnLoad(const std::shared_ptr<Entity> &entity);
	void OnTickStart();
	void OnTickStart(const std::shared_ptr<Entity> &entity);
	void Tick(const std::shared_ptr<Entity> &entity);

	void UpdateBodyPosition(glm::dvec3 &pPosition, glm::dvec3 &pVelocity, double tickDeltaTime);
	void UpdateBodyVelocity(glm::dvec3 &pVelocity, glm::dvec3 &resultantForce, const double &pMass, const double &tickDeltaTime);
	void ApplyGravity(glm::dvec3 & pVelocity, const double &tickDeltaTime);
};
#endif