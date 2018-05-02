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
	bool CollisionSpherePlane(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pCubeEntity);
	bool CollisionSphereSphere(const std::shared_ptr<Entity> &pSphereEntity, const std::shared_ptr<Entity> &pSphereEntity2);
	glm::dvec3 PlaneToPoint(const glm::dvec3 &pPlaneNormal, const glm::dvec3 &pPlanePosition, glm::dvec3& pPoint);
};
#endif
