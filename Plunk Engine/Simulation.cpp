#include "Simulation.h"

#include <random>
#include <chrono>

float GenerateRandomNum(const float & min, const float & max)
{
	std::mt19937_64 rng;

	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);

	// initialize a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> unif(min, max);

	// generate random number
	return unif(rng);
}

//code testing the creation of en entity with components added 
void AddEntitiesToManager(EntityManager &entityManager)
{
	std::map <string, glm::vec3> colours;
	colours.insert(std::pair<string, glm::vec3>("Violet", glm::vec3(148, 0, 211)));
	colours.insert(std::pair<string, glm::vec3>("Indigo", glm::vec3(75, 0, 130)));
	colours.insert(std::pair<string, glm::vec3>("Blue", glm::vec3(0, 0, 255)));
	colours.insert(std::pair<string, glm::vec3>("Green", glm::vec3(0, 255, 0)));
	colours.insert(std::pair<string, glm::vec3>("Yellow", glm::vec3(255, 255, 0)));
	colours.insert(std::pair<string, glm::vec3>("Orange", glm::vec3(255, 127, 0)));
	colours.insert(std::pair<string, glm::vec3>("Red", glm::vec3(255, 0, 0)));

	for (int i = 0; i < 25; i++)
	{
		Entity entity("sphere");
		entity.AddComponent(ComponentRigidBody(glm::vec3(GenerateRandomNum(-8, 8), GenerateRandomNum(3, 10), GenerateRandomNum(-8, 8))));
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Sphere));
		entity.AddComponent(ComponentModel(std::string("models/primitives/icosphere/icosphere4.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}
}

Simulation::Simulation(GLFWwindow *const pWindow) :
	entityManager(EntityManager()),
	inputManager(InputManager()),
	systemManager(SystemManager()),
	systemPhysics(SystemPhysics()),
	systemCollision(SystemCollision()),
	systemShadows(SystemShadows()),
	systemLighting(SystemLighting()),
	systemRender(SystemRender()),
	mCamera(Camera(glm::vec3(0.0f, 5.0f, 50.0f)))
{
	systemManager.AddSystem(systemPhysics);
	systemManager.AddSystem(systemCollision);
	systemManager.AddSystem(systemShadows);  // Shadow setting must be performed before render
	systemManager.AddSystem(systemLighting); // Lighting must be performed before render
	systemManager.AddSystem(systemRender);

	inputManager.setInputCallbacks(pWindow);
	AddEntitiesToManager(entityManager);
	systemManager.LoadSystems(entityManager, this);
}

Simulation::~Simulation()
{}

void Simulation::Run()
{
	systemManager.ActionSystems(entityManager);
}