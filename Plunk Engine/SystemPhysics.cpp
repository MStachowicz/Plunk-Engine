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
		RigidBodyComponent->previousPosition = RigidBodyComponent->position;
		UpdateBodyPosition(RigidBodyComponent->position, RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);

		if (applyGravity)
			if (RigidBodyComponent->mApplyGravity)
			{
				RigidBodyComponent->previousVelocity = RigidBodyComponent->velocity;
				ApplyGravity(RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);
			}
	}
}

// Performs the Euler integration to find the position of the body after a timestep forward.
void SystemPhysics::UpdateBodyPosition(glm::dvec3 &pPosition, glm::dvec3 &pVelocity, double tickDeltaTime)
{
	pPosition = pPosition + (tickDeltaTime * pVelocity);
}

void SystemPhysics::ApplyGravity(glm::dvec3& pVelocity, const double& tickDeltaTime)
{
	pVelocity = pVelocity + (tickDeltaTime * glm::dvec3(0.0f, -9.81f, 0.0f));
}