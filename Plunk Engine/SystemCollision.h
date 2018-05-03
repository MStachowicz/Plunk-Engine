#ifndef SYSTEMCOLLISION_H
#define SYSTEMCOLLISION_H

#include <iostream>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ISystem.h"
#include "EntityManager.h"
#include "ComponentCollision.h"
#include "ComponentRigidBody.h"

class EntityManager;

class SystemCollision : public ISystem
{
public:
	SystemCollision();
	~SystemCollision();
	
	void OnLoad(const std::shared_ptr<Entity>& entity);
	void OnTickStart();
	void OnTickStart(const std::shared_ptr<Entity> &entity);
	void Tick(const std::shared_ptr<Entity>& entity);

private:
	// Performs the collision response between two rigid bodies.
	void CollisionResponse(const std::shared_ptr<ComponentRigidBody>& pCollider, const std::shared_ptr<ComponentRigidBody>& pColliding, const glm::dvec3& pCollisionPoint);
	// Checks for a collision between a moving sphere and a static plane (performs the collision response upon detection).
	bool CollisionSpherePlane(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pCubeEntity);
	// Checks for a collision between two moving spheres (performs the collision response upon detection).
	bool CollisionSphereSphere(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pSphereEntity2);

	// UTILITY FUNCTIONS
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Returns the closest point on the plane to a point.
	glm::dvec3 ClosestPointOnPlane(const std::shared_ptr<RigidBodyPlane>& plane, const glm::dvec3& pPoint); 
	// Returns the signed distance from a point to the plane.
	double DistancePointToPlane(const std::shared_ptr<RigidBodyPlane>& plane, const glm::dvec3& pPoint);
	// Returns the closest point on a sphere to a point (not signed).
	glm::dvec3 ClosestPointOnSphere(const std::shared_ptr<RigidBodySphere>& pSphere, const glm::dvec3& pPoint);
	// Returns the closest point on a sphere to a point (not signed).
	glm::dvec3 ClosestPointOnSphere(const glm::dvec3& pSphereCenter, const double& pSphereRadius, const glm::dvec3& pPoint);
};
#endif
