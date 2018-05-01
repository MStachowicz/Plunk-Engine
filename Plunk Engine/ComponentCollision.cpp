#include "ComponentCollision.h"

ComponentCollision::~ComponentCollision()
{}

ComponentCollision::ComponentCollision(collisionPrimitiveType pType) : 
	IComponent(IComponent::ComponentFlags::COMPONENT_COLLISION), type(pType)
{}

void ComponentCollision::AddCollision(Entity & entityCollidedWith, glm::vec3 &collisionPoint)
{
	collisions.push_back(CollisionData(entityCollidedWith, collisionPoint));
}