#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "IComponent.h"
#include <glm/glm.hpp>

class ComponentRigidBody : public IComponent
{
public:
	ComponentRigidBody(const glm::vec3& pPosition);
	~ComponentRigidBody();

	glm::vec3 position; // Current position of the body
	glm::vec3 velocity; // Current velocity of the body
	float mass; // Mass of the body
	bool mApplyGravity;

	virtual const glm::vec3& GetScale() const;
	virtual const glm::vec3& GetRotation() const;
	virtual void Rotate(const glm::vec3& pRotation);

protected:
	glm::vec3 mRotation; // Current rotation of the body
	glm::vec3 scale; // Scale of the body
};

// DERIVED RIGID BODIES
///////////////////////////////////////////////////////////////////

class RigidBodySphere : public ComponentRigidBody
{
public:
	RigidBodySphere(const glm::vec3& pStartingPosition, const float& pRadius);

	float mRadius;

	const glm::vec3& GetScale() const;
};

class RigidBodyPlane : public ComponentRigidBody
{
public:
	RigidBodyPlane(const glm::vec3& pStartingPosition, const glm::vec3& pRotation);

	const glm::vec3& GetNormal() const;
	void Rotate(const glm::vec3& pRotation);

private:
	glm::vec3 mNormal;
};

class RigidBodyCylinder : public ComponentRigidBody
{
public:
	RigidBodyCylinder(const glm::vec3& pStartingPosition, const float& pLength, const float& pRadius);

	float mLength;
	float mRadius;

	const glm::vec3& GetScale() const;
};

#endif