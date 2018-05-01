#ifndef COMPONENTCOLLISION_H
#define COMPONENTCOLLISION_H

#include <glm\glm.hpp>
#include "IComponent.h"

class Entity;

class ComponentCollision : public IComponent
{
public:
	enum collisionPrimitiveType
	{
		Sphere,
		Plane,
		Cylinder,
		Cube,
	};

	struct PrimitiveGeometry
	{
		glm::vec3 normal;
	};

	struct Cylinder : public PrimitiveGeometry
	{

	};

	ComponentCollision(collisionPrimitiveType pType);
	~ComponentCollision();

	collisionPrimitiveType type;
};
#endif
