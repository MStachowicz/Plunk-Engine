#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "IComponent.h"
#include "IStateMachine.h"
#include <glm/glm.hpp>

enum RigidBodyState
{
	ACTIVE, SLEEPING
};

class ComponentRigidBody : public IComponent, public IStateMachine<RigidBodyState>
{
public:
	ComponentRigidBody(const glm::dvec3& pPosition);
	~ComponentRigidBody();

	glm::dvec3 position; // Position of the body at this timestep.
	glm::dvec3 velocity; // Velocity of the body at this timestep.
	glm::dvec3 previousVelocity; // Velocity of the body at the previous timestep.
	glm::dvec3 previousPosition; // Position of the body at the previous timestep.
	double mass; // Mass of the body
	bool mApplyGravity;

	virtual const glm::dvec3& GetScale() const;
	virtual const glm::dvec3& GetRotation() const;
	virtual void Rotate(const glm::dvec3& pRotation);

	void ChangeState(const RigidBodyState& pNewState);

protected:
	glm::dvec3 mRotation; // Current rotation of the body
	glm::dvec3 scale; // Scale of the body
};

// DERIVED RIGID BODIES
///////////////////////////////////////////////////////////////////

class RigidBodySphere : public ComponentRigidBody
{
public:
	RigidBodySphere(const glm::dvec3& pStartingPosition, const double& pRadius);

	double mRadius;

	const glm::dvec3& GetScale() const;
};

class RigidBodyPlane : public ComponentRigidBody
{
public:
	RigidBodyPlane(const glm::dvec3& pStartingPosition, const glm::dvec3& pRotation);

	const glm::dvec3& GetNormal() const;
	void Rotate(const glm::dvec3& pRotation);

private:
	glm::dvec3 mNormal;
};

class RigidBodyCylinder : public ComponentRigidBody
{
public:
	RigidBodyCylinder(const glm::dvec3& pStartingPosition, const double& pLength, const double& pRadius);

	double mLength;
	double mRadius;

	const glm::dvec3& GetScale() const;
};

#endif