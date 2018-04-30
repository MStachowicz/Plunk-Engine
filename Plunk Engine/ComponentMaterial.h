#ifndef COMPONENTMATERIAL_H
#define COMPONENTMATERIAL_H

#include "IComponent.h"
#include <glm/glm.hpp>

// Allows an entity to be rendered with a material surface as opposed to a textured one.
class ComponentMaterial : public IComponent
{
public:
	glm::vec3 ambient = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(0.0f);
	glm::vec3 specular = glm::vec3(0.0f);
	float shininess = 0;

	ComponentMaterial();
	ComponentMaterial(glm::vec3 pAmbientDiffuse);
	ComponentMaterial(glm::vec3 pAmbientDiffuse, glm::vec3 pSpecular);
	ComponentMaterial(glm::vec3 pAmbientDiffuse, glm::vec3 pSpecular, float pShininess);
	ComponentMaterial(glm::vec3 pAmbient, glm::vec3 pDiffuse, glm::vec3 pSpecular, float pShininess);

	~ComponentMaterial();

private:
	const float DEFAULTSHININESS = 64.0f;
};
#endif