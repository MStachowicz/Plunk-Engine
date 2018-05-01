#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "IComponent.h"
#include <glm/glm.hpp>

class ComponentRigidBody : public IComponent
{
public:

	ComponentRigidBody(glm::vec3 pos);
	~ComponentRigidBody();

	glm::vec3 position; // Current position of the body
	glm::vec3 velocity; // Current velocity of the body
	bool mApplyGravity;

	virtual glm::vec3 GetScale() = 0;
	virtual glm::vec3 GetRotation() = 0;
	virtual glm::vec3 SetRotation() = 0;

protected:
	glm::vec3 rotation; // Current rotation of the body
	glm::vec3 scale; // Scale of the body
	float mass; // Mass of the body
};

class RigidBodySphere : public ComponentRigidBody
{
public:
	float mRadius;
	glm::vec3 GetScale();
};

class RigidBodyPlane : public ComponentRigidBody
{
public:
	glm::vec3 mNormal;
	glm::vec3 GetScale();
};

class RigidBodyCylinder : public ComponentRigidBody
{
public:
	float mLength;
	float mRadius;
	glm::vec3 GetScale();
};


#endif