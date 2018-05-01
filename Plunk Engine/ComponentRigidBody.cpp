#include "ComponentRigidBody.h"

ComponentRigidBody::ComponentRigidBody(glm::vec3 pos) :
	IComponent(IComponent::ComponentFlags::COMPONENT_RIGID_BODY),
	mass(1.f),
	scale(1.f),
	velocity(0.f),
	position(pos),
	mApplyGravity(true)
{}

ComponentRigidBody::~ComponentRigidBody()
{}

glm::vec3 RigidBodySphere::GetScale()
{
	return glm::vec3(mRadius, mRadius, mRadius);
}
