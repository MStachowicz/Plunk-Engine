#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "IComponent.h"

class Entity
{
public:
	std::string mName; // Name of the entity. Used for debugging purposes
	IComponent::ComponentFlags mMask; // The bitwise mask used to match appropriate systems to this entity

	Entity(std::string pName) : mName(pName)
	{}
	~Entity()
	{}

	// Returns the adress of the component in the entity mComponentList or nullptr if not found.
	IComponent* FindComponent(const int& pComponentValue)
	{
		// Find the ComponentFlags type of the component
		auto findComponentType = [pComponentValue](auto component)
		{
			return component->componentType == pComponentValue;
		};

		// Find the location of the component in the mComponentList
		auto component_it = std::find_if(mComponentList.begin(), mComponentList.end(), findComponentType);

		if (component_it == end(mComponentList)) // If element not found, return empty component
		{
			return nullptr;
		}
		else // otherwise return the adress of the component.
		{
			return component_it->get();
		}
	}

	template <typename CompType>
	// Adds a single component to the mComponentList and updates the mMask
	void AddComponent(CompType& pComponent)
	{
		mComponentList.push_back(std::make_unique<CompType>(pComponent));
		UpdateMask(pComponent);
	}

private:
	std::vector <std::unique_ptr<IComponent>> mComponentList; // All the components making up this entity
	
	void UpdateMask(IComponent &component)  // Updates the mask of the entity with the new component
	{
		// Update the entity mask with the newly added component type
		unsigned int tempMask = static_cast<int>(mMask); // casting mask to int to perform bitwise set operation
		tempMask |= static_cast<int>(component.GetComponentType());
		mMask = (IComponent::ComponentFlags)tempMask; // Assign the new value of the mask
	}
};
#endif