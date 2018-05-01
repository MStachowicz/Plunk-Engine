#include "ComponentRigidBody.h"
#include <glm/gtc/matrix_transform.hpp>

ComponentRigidBody::ComponentRigidBody(const glm::vec3& pPosition) :
	IComponent(IComponent::ComponentFlags::COMPONENT_RIGID_BODY),
	position(pPosition),
	velocity(0.f),
	mass(1.f),
	mApplyGravity(true),
	mRotation(0.f),
	scale(1.f)
{}

ComponentRigidBody::~ComponentRigidBody()
{}

const glm::vec3 & ComponentRigidBody::GetScale() const
{
	return scale;
}

const glm::vec3 & ComponentRigidBody::GetRotation() const
{
	return mRotation;
}

void ComponentRigidBody::Rotate(const glm::vec3 & pRotation)
{
	mRotation = pRotation;
}



// SPHERE
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodySphere::RigidBodySphere(const glm::vec3 & pStartingPosition, const float & pRadius) :
	ComponentRigidBody(pStartingPosition),
	mRadius(pRadius)
{}

const glm::vec3 & RigidBodySphere::GetScale() const
{
	return glm::vec3(mRadius * 2);
}

// PLANE
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodyPlane::RigidBodyPlane(const glm::vec3 & pStartingPosition, const glm::vec3 & pRotation) :
	ComponentRigidBody(pStartingPosition),
	mNormal(glm::vec3(0.f, 1.f, 0.f)) // Default model file is a plane parallel to the z-axis with normal +y
{
	Rotate(pRotation);
}

const glm::vec3 & RigidBodyPlane::GetNormal() const
{
	return mNormal;
}

void RigidBodyPlane::Rotate(const glm::vec3 & pRotation)
{
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(pRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(pRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(pRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	mNormal = glm::vec3(rotMatrix * glm::vec4(mNormal, 1.0f));
	mRotation = pRotation;
}

// CYLINDER
////////////////////////////////////////////////////////////////////////////////////////////////////////
RigidBodyCylinder::RigidBodyCylinder(const glm::vec3 & pStartingPosition, const float & pLength, const float & pRadius) :
	ComponentRigidBody(pStartingPosition),
	mLength(pLength),
	mRadius(pRadius)
{}

const glm::vec3 & RigidBodyCylinder::GetScale() const
{
	return glm::vec3(mRadius * 2, mLength, mRadius * 2);
}
