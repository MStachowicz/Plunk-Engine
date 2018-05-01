#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "IComponent.h"
#include <glm/glm.hpp>

class ComponentRigidBody : public IComponent
{
public:
	ComponentRigidBody();
	ComponentRigidBody(float x, float y, float z);
	ComponentRigidBody(glm::vec3 pos);
	~ComponentRigidBody();
	
	glm::vec3 position; // Current position of the body
	glm::vec3 rotation; // Current rotation of the body
	glm::vec3 velocity; // Current velocity of the body
	float scale; // Scale of the body
	float mass; // Mass of the body
	bool mApplyGravity;

private:
};
#endif