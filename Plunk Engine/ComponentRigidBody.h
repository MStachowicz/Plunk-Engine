#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "IComponent.h"
#include <glm/glm.hpp>

class ComponentRigidBody : public IComponent
{
public:
	ComponentRigidBody(const glm::dvec3& pPosition);
	~ComponentRigidBody();

	glm::dvec3 position; // Current position of the body
	glm::dvec3 velocity; // Current velocity of the body
	double mass; // Mass of the body
	bool mApplyGravity;

	virtual const glm::dvec3& GetScale() const;
	virtual const glm::dvec3& GetRotation() const;
	virtual void Rotate(const glm::dvec3& pRotation);

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