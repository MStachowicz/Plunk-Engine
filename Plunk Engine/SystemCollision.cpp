#include "SystemCollision.h"
#include "Simulation.h"

SystemCollision::SystemCollision() :
	ISystem("SystemCollision",
	(IComponent::ComponentFlags)(IComponent::COMPONENT_RIGID_BODY | IComponent::COMPONENT_COLLISION))
{}

SystemCollision::~SystemCollision()
{}

void SystemCollision::OnLoad(const std::shared_ptr<Entity> &entity)
{}

void SystemCollision::OnTickStart()
{}

void SystemCollision::OnTickStart(const std::shared_ptr<Entity>& entity)
{}

void SystemCollision::Tick(const std::shared_ptr<Entity>& entity)
{
	if ((entity->mask & MASK) == MASK)
	{
		std::shared_ptr<ComponentRigidBody> RigidBodyComponent = std::dynamic_pointer_cast<ComponentRigidBody> (entity->FindComponent(65536));
		std::shared_ptr<ComponentCollision> collisionComp = std::dynamic_pointer_cast<ComponentCollision> (entity->FindComponent(32768));

		for (unsigned int i = 0; i < mSimulationInstance->entityManager.entityList.size(); i++)
		{
			if ((mSimulationInstance->entityManager.entityList[i]->mask & MASK) == MASK) // if the entity is collidable 
			{
				if (entity != mSimulationInstance->entityManager.entityList[i]) // if it is not the same entity as currently being checked
				{
					// Retrieve all the components that will be checked against.
					std::shared_ptr<ComponentRigidBody> RigidBodyComponent2 = std::dynamic_pointer_cast<ComponentRigidBody> (mSimulationInstance->entityManager.entityList[i]->FindComponent(65536));
					std::shared_ptr<ComponentCollision> collisionComp2 = std::dynamic_pointer_cast<ComponentCollision> (mSimulationInstance->entityManager.entityList[i]->FindComponent(32768));

					switch (collisionComp->type)
					{
					case ComponentCollision::collisionPrimitiveType::Sphere:

						switch (collisionComp2->type)
						{
						case ComponentCollision::collisionPrimitiveType::Sphere:
						{
							// SPHERE V SPHERE CHECK
							// --------------------------------------------------------------------------------------------------
							CollisionSphereSphere(entity, mSimulationInstance->entityManager.entityList[i]);
							break;
						}
						case ComponentCollision::collisionPrimitiveType::Plane:
						{
							// SPHERE V PLANE CHECK
							// --------------------------------------------------------------------------------------------------
							CollisionSpherePlane(entity, mSimulationInstance->entityManager.entityList[i]);
							break;
						}
						}
						break;
					}
				}
			}
		}
	}
}


bool SystemCollision::CollisionSphereSphere(const std::shared_ptr<Entity>& pSphereEntity, const std::shared_ptr<Entity>& pSphere2Entity)
{
	std::shared_ptr<RigidBodySphere> sphereRigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphereEntity->FindComponent(65536));
	std::shared_ptr<RigidBodySphere> sphere2RigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphere2Entity->FindComponent(65536));

	glm::vec3 sphere1toSphere2 = sphere2RigidBody->position - sphereRigidBody->position;
	float distance = glm::length(sphere1toSphere2) - (sphereRigidBody->mRadius + sphere2RigidBody->mRadius);

	if (distance < 0)
	{
		glm::vec3 relativeVelocity = sphereRigidBody->velocity - sphere2RigidBody->velocity;
		glm::vec3 collisionNormal = sphereRigidBody->position - (sphereRigidBody->position + glm::normalize(sphere1toSphere2) * sphereRigidBody->mRadius);

		float restitution = 1.0f;

		if (glm::dot(relativeVelocity, collisionNormal) < 0)
		{
			float impulseMagnitude = glm::dot((-1 * (1 + restitution) * relativeVelocity), collisionNormal) /
				glm::dot(collisionNormal, (collisionNormal * ((1 / sphereRigidBody->mass) + (1 / sphere2RigidBody->mass))));

			// Apply an instant change in momentum/velocity using the calculated impulse
			sphereRigidBody->velocity = sphereRigidBody->velocity + ((impulseMagnitude / sphereRigidBody->mass) * collisionNormal);
			sphere2RigidBody->velocity = sphere2RigidBody->velocity - ((impulseMagnitude / sphere2RigidBody->mass) * collisionNormal);

			return true;
		}
	}

	return false;
}

// Finds the magnitude of the vector between the sphere and the closest point on a plane comparing it to the sphere radius.
bool SystemCollision::CollisionSpherePlane(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pPlaneEntity)
{
	std::shared_ptr<RigidBodySphere> sphereRigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphereEntity->FindComponent(65536));
	std::shared_ptr<RigidBodyPlane> planeRigidBody = std::dynamic_pointer_cast<RigidBodyPlane> (pPlaneEntity->FindComponent(65536));

	glm::vec3 sphereToClosestPoint = PlaneToPoint(planeRigidBody->GetNormal(), planeRigidBody->position, sphereRigidBody->position) - sphereRigidBody->position;

	// The signed distance from the sphere center to the closest point on the plane
	float distance = glm::length(sphereToClosestPoint);
	distance -= sphereRigidBody->mRadius;

	// If a collision is detected
	if (distance <= 0)
	{
		// Reverse the plane normal if sphere is behind the plane
		glm::vec3 sphereToPlane(sphereRigidBody->position - planeRigidBody->position);
		float dot = glm::dot(sphereToPlane, planeRigidBody->GetNormal());
		glm::vec3 flippedPlaneNormal = planeRigidBody->GetNormal();
		if (dot < 0)
		{
			flippedPlaneNormal *= -1;
		}


		// Find how long ago (t) the collision occurred and move the sphere back that timestep
		float t = abs(distance) / glm::length(sphereRigidBody->velocity);
		sphereRigidBody->position = sphereRigidBody->position + (t * -sphereRigidBody->velocity);

		// how far along the normal of the plane from sphere = collision point
		glm::vec3 collisionPoint = sphereRigidBody->position - (flippedPlaneNormal * sphereRigidBody->mRadius);


		// Collision response
		glm::vec3 relativeVelocity = sphereRigidBody->velocity - planeRigidBody->velocity;
		glm::vec3 collisionNormal = glm::normalize(sphereRigidBody->position - collisionPoint);

		float restitution = 1.0f;

		float impulseMagnitude = glm::dot((-1 * (1 + restitution) * relativeVelocity), collisionNormal) /
			glm::dot(collisionNormal, (collisionNormal * ((1 / sphereRigidBody->mass) + (1 / planeRigidBody->mass))));

		if (glm::dot(relativeVelocity, collisionNormal) < 0)
		{
			sphereRigidBody->velocity = sphereRigidBody->velocity + ((impulseMagnitude / sphereRigidBody->mass) * collisionNormal);
			planeRigidBody->velocity = planeRigidBody->velocity - ((impulseMagnitude / planeRigidBody->mass) * collisionNormal);
		}

		return true;
	}
	else
		return false;
}
// Returns the shortest vector from the plane to the point. (pg 165 collision detection)
glm::vec3 SystemCollision::PlaneToPoint(const glm::vec3 &pPlaneNormal, const glm::vec3 &pPlanePosition, glm::vec3& pPoint)
{
	float pointToPlaneDistance = glm::dot((pPoint - pPlanePosition), pPlaneNormal);

	// calculates how many units of plane normal length equal the point
	return glm::vec3(pPoint - (pointToPlaneDistance * pPlaneNormal));
}