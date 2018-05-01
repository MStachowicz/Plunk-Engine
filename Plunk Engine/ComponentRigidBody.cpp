#include "ComponentRigidBody.h"

ComponentRigidBody::ComponentRigidBody() :
	IComponent(IComponent::ComponentFlags::COMPONENT_RIGID_BODY),
	mass(1.f),
	scale(1.f),
	velocity(0.f),
	position(glm::vec3(0)),
	mApplyGravity(true)
{}

ComponentRigidBody::ComponentRigidBody(float x, float y, float z) :
	IComponent(IComponent::ComponentFlags::COMPONENT_RIGID_BODY),
	mass(1.f),
	scale(1.f),
	velocity(0.f),
	position(glm::vec3(x, y, z)),
	mApplyGravity(true)
{}

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