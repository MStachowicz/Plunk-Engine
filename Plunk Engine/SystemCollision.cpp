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

		if (RigidBodyComponent->GetState() != RigidBodyState::SLEEPING) // Sleeping bodies do not move so dont check for collisions
			for (unsigned int i = 0; i < mSimulationInstance->entityManager.entityList.size(); i++) // Checking all the other entities if: they have the collidable component, 
				if ((mSimulationInstance->entityManager.entityList[i]->mask & MASK) == MASK) // Entity to collide with must have the collidable component.
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

// Performs the collision response between two rigid bodies.
void SystemCollision::CollisionResponse(const std::shared_ptr<ComponentRigidBody>& pCollider, const std::shared_ptr<ComponentRigidBody>& pColliding, const glm::dvec3 & pCollisionPoint)
{
	glm::dvec3 relativeVelocity = pCollider->velocity - pColliding->velocity;
	glm::dvec3 collisionNormal = glm::normalize(pCollider->position - pCollisionPoint);

	// If the relative velocity is pointing away from the normal perform the response
	if (glm::dot(relativeVelocity, collisionNormal) < 0)
	{
		double impulseMagnitude = glm::dot((-1 * (1 + mSimulationInstance->mRestitutionCoefficient) * relativeVelocity), collisionNormal) /
			glm::dot(collisionNormal, (collisionNormal * ((1 / pCollider->mass) + (1 / pColliding->mass))));

		// Apply an instant change in momentum/velocity using the calculated impulse
		pCollider->velocity = pCollider->velocity + ((impulseMagnitude / pCollider->mass) * collisionNormal);
		pColliding->velocity = pColliding->velocity - ((impulseMagnitude / pColliding->mass) * collisionNormal);
	}
	else
	{
		std::cout << "SYSTEMCOLLISION::COLLISIONRESPONSE::ERROR Collision registered during object penetration (ignored)." << std::endl;
	}
}

// Checks for a collision between two moving spheres (performs the collision response upon detection).
bool SystemCollision::CollisionSphereSphere(const std::shared_ptr<Entity>& pSphereEntity, const std::shared_ptr<Entity>& pSphere2Entity)
{
	std::shared_ptr<RigidBodySphere> sphereRigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphereEntity->FindComponent(65536));
	std::shared_ptr<RigidBodySphere> sphere2RigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphere2Entity->FindComponent(65536));

	glm::dvec3 sphere1toSphere2 = sphere2RigidBody->position - sphereRigidBody->position;
	double distance = glm::length(sphere1toSphere2) - (sphereRigidBody->mRadius + sphere2RigidBody->mRadius);

	if (distance < 0)
	{
		glm::dvec3 collisionPoint = sphereRigidBody->position + glm::normalize(sphere1toSphere2) * sphereRigidBody->mRadius;
		CollisionResponse(sphereRigidBody, sphere2RigidBody, collisionPoint);
		return true;
	}

	return false;
}

// Checks for a collision between a moving sphere and a static plane (performs the collision response upon detection).
bool SystemCollision::CollisionSpherePlane(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pPlaneEntity)
{
	std::shared_ptr<RigidBodySphere> sphereRigidBody = std::dynamic_pointer_cast<RigidBodySphere> (pSphereEntity->FindComponent(65536));
	std::shared_ptr<RigidBodyPlane> planeRigidBody = std::dynamic_pointer_cast<RigidBodyPlane> (pPlaneEntity->FindComponent(65536));

	// Finding the distance between the closest point on the plane to the closest point on the sphere. 
	// The point on the plane closest to the sphere, also the collision point if they overlap.
	glm::dvec3 clsPtPlane = ClosestPointOnPlane(planeRigidBody, sphereRigidBody->position);
	glm::dvec3 clsPtSphere = ClosestPointOnSphere(sphereRigidBody->position, sphereRigidBody->mRadius, clsPtPlane);
	double distance = DistancePointToPlane(planeRigidBody, clsPtSphere);

	// If the sphere overlaps the plane the distance is negative
	if (distance <= 0)
	{
		// If the velocity is below the threshold the sphere is put to sleep
		if (glm::length(sphereRigidBody->velocity) < 0.08)
		{
			sphereRigidBody->ChangeState(RigidBodyState::SLEEPING);
			return false;
		}

		// 1. Check which side of the plane the sphere is on. Flip the normal if behind the plane.
		glm::dvec3 planeToSphere = sphereRigidBody->position - planeRigidBody->position;
		double dot = glm::dot(planeToSphere, planeRigidBody->GetNormal());
		glm::dvec3 flippedPlaneNormal = planeRigidBody->GetNormal();
		if (dot < 0)
		{
			flippedPlaneNormal *= -1;
		}

		// 2. Find the time to collision from the previous position and changing velocity.
		// Find the previous distance
		glm::dvec3 previousClsPtPlane = ClosestPointOnPlane(planeRigidBody, sphereRigidBody->previousPosition);
		glm::dvec3 previousClsPtSphere = ClosestPointOnSphere(sphereRigidBody->previousPosition, sphereRigidBody->mRadius, previousClsPtPlane);

		double previousDistance = DistancePointToPlane(planeRigidBody, previousClsPtSphere);
		double acceleration = 9.81;
		double initialVelocity = abs(sphereRigidBody->previousVelocity.y); // Only the y component of initial velocity is used as gravity is the only accelerant.
		// Solving quadratic equation for time to collision from the previous position and initial velocity.
		double timeStepToCollision = abs((-initialVelocity + glm::sqrt(glm::pow(initialVelocity, 2.0) + (2 * acceleration * previousDistance)))
			/ acceleration);

		// Set the position and velocity to values at the point of collision
		sphereRigidBody->position = sphereRigidBody->previousPosition + (timeStepToCollision * sphereRigidBody->previousVelocity);
		sphereRigidBody->velocity = sphereRigidBody->previousVelocity + (glm::dvec3(0.0, -9.81, 0.0) * timeStepToCollision);


		// 3. Perform collision response
		CollisionResponse(sphereRigidBody, planeRigidBody, clsPtPlane);
		return true;
	}
	else
		return false;
}

// UTILITY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns the closest point on the plane to a point.
glm::dvec3 SystemCollision::ClosestPointOnPlane(const std::shared_ptr<RigidBodyPlane>& plane, const glm::dvec3 & pPoint)
{
	double distance = glm::dot(plane->position, plane->GetNormal());
	glm::dvec3 point = pPoint + ((distance - glm::dot(pPoint, plane->GetNormal())) * plane->GetNormal());
	return point;
}

// Returns the signed distance from a point to the plane.
double SystemCollision::DistancePointToPlane(const std::shared_ptr<RigidBodyPlane>& plane, const glm::dvec3 & pPoint)
{
	double pointToPlaneDistance = glm::dot((pPoint - plane->position), plane->GetNormal());
	return pointToPlaneDistance;
}

// Returns the closest point on a sphere to a point (not signed).
glm::dvec3 SystemCollision::ClosestPointOnSphere(const std::shared_ptr<RigidBodySphere>& pSphere, const glm::dvec3 & pPoint)
{
	glm::dvec3 pointToSphereCenter = pSphere->position - pPoint;
	// Scale the vector from the point to sphere center by the radius.
	glm::dvec3 pointToSphereSurface = pointToSphereCenter * ((glm::length(pointToSphereCenter) - pSphere->mRadius) / glm::length(pointToSphereCenter));
	// Project the displacement onto the sphere
	glm::dvec3 point = pPoint + pointToSphereCenter;

	return point;
}

// Returns the closest point on a sphere to a point (not signed).
glm::dvec3 SystemCollision::ClosestPointOnSphere(const glm::dvec3 & pSphereCenter, const double & pSphereRadius, const glm::dvec3 & pPoint)
{
	glm::dvec3 pointToSphereCenter = pSphereCenter - pPoint;
	// Scale the vector from the point to sphere center by the radius.
	glm::dvec3 pointToSphereSurface = ((glm::length(pointToSphereCenter) - pSphereRadius) / glm::length(pointToSphereCenter)) *  pointToSphereCenter;
	// Project the displacement onto the sphere
	glm::dvec3 point = pPoint + pointToSphereSurface;

	return point;
}
