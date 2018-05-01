#include "SystemPhysics.h"
#include "Simulation.h"

SystemPhysics::SystemPhysics() :
	ISystem("SystemPhysics", (IComponent::ComponentFlags)(IComponent::COMPONENT_RIGID_BODY)),
	applyGravity(true)
{}

SystemPhysics::~SystemPhysics()
{}

void SystemPhysics::OnLoad(const std::shared_ptr<Entity> &entity)
{}

void SystemPhysics::OnTickStart()
{}

void SystemPhysics::OnTickStart(const std::shared_ptr<Entity>& entity)
{}

void SystemPhysics::Tick(const std::shared_ptr<Entity> &entity)
{
	if ((entity->mask & MASK) == MASK)
	{
		std::shared_ptr<ComponentRigidBody> RigidBodyComponent =
			std::dynamic_pointer_cast<ComponentRigidBody> (entity->FindComponent(65536));

		// LINEAR DYNAMICS
		//------------------------------------------------------------------------------------------------------
		UpdateBodyPosition(RigidBodyComponent->position, RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);

		if (applyGravity)
			if (RigidBodyComponent->mApplyGravity)
				ApplyGravity(RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);
	}
}

// Performs the Euler integration to find the position of the body after a timestep forward.
void SystemPhysics::UpdateBodyPosition(glm::vec3 &pPosition, glm::vec3 &pVelocity, float tickDeltaTime)
{
	pPosition = pPosition + (tickDeltaTime * pVelocity);
}

void SystemPhysics::ApplyGravity(glm::vec3& pVelocity, const float& tickDeltaTime)
{
	pVelocity = pVelocity + (tickDeltaTime * glm::vec3(0.0f, -9.81f, 0.0f));
}