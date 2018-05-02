#include "ComponentRigidBody.h"
#include <glm/gtc/matrix_transform.hpp>

ComponentRigidBody::ComponentRigidBody(const glm::dvec3& pPosition) :
	IComponent(IComponent::ComponentFlags::COMPONENT_RIGID_BODY),
	position(pPosition),
	velocity(0.),
	mass(1.),
	mApplyGravity(true),
	mRotation(0.),
	scale(1.)
{}

ComponentRigidBody::~ComponentRigidBody()
{}

const glm::dvec3 & ComponentRigidBody::GetScale() const
{
	return scale;
}

const glm::dvec3 & ComponentRigidBody::GetRotation() const
{
	return mRotation;
}

void ComponentRigidBody::Rotate(const glm::dvec3 & pRotation)
{
	mRotation = pRotation;
}



// SPHERE
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodySphere::RigidBodySphere(const glm::dvec3 & pStartingPosition, const double & pRadius) :
	ComponentRigidBody(pStartingPosition),
	mRadius(pRadius)
{}

const glm::dvec3 & RigidBodySphere::GetScale() const
{
	return glm::vec3(mRadius * 2);
}

// PLANE
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodyPlane::RigidBodyPlane(const glm::dvec3 & pStartingPosition, const glm::dvec3 & pRotation) :
	ComponentRigidBody(pStartingPosition),
	mNormal(glm::dvec3(0.f, 1.f, 0.f)) // Default model file is a plane parallel to the z-axis with normal +y
{
	Rotate(pRotation);
	scale = glm::dvec3(2000);
}

const glm::dvec3 & RigidBodyPlane::GetNormal() const
{
	return mNormal;
}

void RigidBodyPlane::Rotate(const glm::dvec3 & pRotation)
{
	glm::dmat4 rotMatrix = glm::rotate(glm::dmat4(1.0f), glm::radians(pRotation.x), glm::dvec3(1.0f, 0.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(pRotation.y), glm::dvec3(0.0f, 1.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(pRotation.z), glm::dvec3(0.0f, 0.0f, 1.0f));

	mNormal = glm::dvec3(rotMatrix * glm::dvec4(mNormal, 1.0f));
	mRotation = pRotation;
}

// CYLINDER
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodyCylinder::RigidBodyCylinder(const glm::dvec3 & pStartingPosition, const double & pLength, const double & pRadius) :
	ComponentRigidBody(pStartingPosition),
	mLength(pLength),
	mRadius(pRadius)
{}

const glm::dvec3 & RigidBodyCylinder::GetScale() const
{
	return glm::dvec3(mRadius * 2, mLength, mRadius * 2);
}
