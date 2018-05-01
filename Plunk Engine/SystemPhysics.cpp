#include "SystemPhysics.h"
#include "Simulation.h"

SystemPhysics::SystemPhysics() :
	ISystem("SystemPhysics", (IComponent::ComponentFlags)(IComponent::COMPONENT_RIGID_BODY)),
	applyGravity(true)
{}

SystemPhysics::~SystemPhysics()
{}

// Applies the velocity to all the entities 
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

		if (!pauseSimulation)
		{
			// LINEAR DYNAMICS
			//------------------------------------------------------------------------------------------------------
			UpdateBodyPosition(RigidBodyComponent->position, RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);

			if (applyGravity)
				if (!RigidBodyComponent->ignorePhysics)
					ApplyGravity(RigidBodyComponent->velocity, mSimulationInstance->mDeltaTime);

			// Resolve all the linear forces applied to the body since the last physics tick updating the resultant force.
			RigidBodyComponent->ApplyForces();

			// Setting the new velocity integrated from the current velocity and acceleration through all the forces applied to the body since the last tick
			UpdateBodyVelocity(RigidBodyComponent->velocity, RigidBodyComponent->resultantForce, RigidBodyComponent->mass, mSimulationInstance->mDeltaTime);
		}
	}
}

// Performs the Euler integration to find the position of the body after a timestep forward.
void SystemPhysics::UpdateBodyPosition(glm::vec3 &pPosition, glm::vec3 &pVelocity, float tickDeltaTime)
{
	pPosition = pPosition + (tickDeltaTime * pVelocity);
}

void SystemPhysics::UpdateBodyVelocity(glm::vec3 & pVelocity, glm::vec3 & resultantForce, const float & pMass, const float & tickDeltaTime)
{
	pVelocity = pVelocity + (tickDeltaTime * (resultantForce / pMass));
}

void SystemPhysics::ApplyGravity(glm::vec3& pVelocity, const float& tickDeltaTime)
{
	pVelocity = pVelocity + (tickDeltaTime * glm::vec3(0.0f, -9.81f, 0.0f));
}