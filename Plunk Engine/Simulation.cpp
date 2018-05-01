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

	for (int i = 0; i < 1; i++)
	{
		Entity entity("sphereBig");
		ComponentRigidBody body = ComponentRigidBody(glm::vec3(0, 20, 0));
		body.mass = 100; body.scale = 10;
		entity.AddComponent(body);
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Sphere));
		entity.AddComponent(ComponentModel(std::string("models/primitives/icosphere/icosphere4.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}

	for (int i = 0; i < 1; i++)
	{
		Entity entity("plane");
		ComponentRigidBody body = ComponentRigidBody(glm::vec3(0, 0, 0));
		body.ignorePhysics = true; body.mass = 1000000000000.f; body.scale = 100;
		entity.AddComponent(body);
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Plane));
		entity.AddComponent(ComponentModel(std::string("models/primitives/plane/plane.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}

	for (int i = 0; i < 1; i++)
	{
		Entity entity("cylinder");
		ComponentRigidBody body = ComponentRigidBody(glm::vec3(0, 0, 45));
		body.ignorePhysics = true; body.mass = 1000000000000.f; body.scale = 1;
		entity.AddComponent(body);
		//entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Plane));
		entity.AddComponent(ComponentModel(std::string("models/primitives/cylinder/cylinder64.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}

	Entity DirLight("DirLight");
	DirLight.AddComponent(ComponentDirectionalLight());
	DirLight.AddComponent(ComponentShadowCast());
	entityManager.AddEntity(DirLight);
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
	mCamera(Camera(glm::vec3(0.0f, 5.0f, 50.0f))),
	mDeltaTime(0.f),
	mCurrentFrame(0.f),
	mLastFrame(0.f),
	mTimeScaling(1.0f),
	mSimulationTime(0.f),
	mSimulationPaused(false)
{
	systemManager.AddSystem(systemPhysics);
	systemManager.AddSystem(systemCollision);
	systemManager.AddSystem(systemShadows);  // Shadow setting must be performed before render
	systemManager.AddSystem(systemLighting); // Lighting must be performed before render
	systemManager.AddSystem(systemRender);

	inputManager.setInputCallbacks(pWindow, this);
	AddEntitiesToManager(entityManager);
	systemManager.LoadSystems(entityManager, this);
}

Simulation::~Simulation()
{}

void Simulation::Run()
{
	// Per frame time logic
	mCurrentFrame = glfwGetTime();
	mDeltaTime = mCurrentFrame - mLastFrame;
	mLastFrame = mCurrentFrame;
	mSimulationTime += mDeltaTime;

	mDeltaTime *= mTimeScaling;

	systemManager.ActionSystems(entityManager);
}

void Simulation::TogglePauseSimulation()
{
	if (mSimulationPaused)
	{
		systemPhysics.mRunning = true;
		systemCollision.mRunning = true;

		mSimulationPaused = false;
	}
	else
	{
		systemPhysics.mRunning = false;
		systemCollision.mRunning = false;

		mSimulationPaused = true;
	}
}

void Simulation::ChangeTimeScaling(double &pAmount)
{
	pAmount *= 0.2;
	mTimeScaling += pAmount;

	if (mTimeScaling < 0.1)
	{
		mTimeScaling = 0.1;
	}
	else if (mTimeScaling > 1)
	{
		mTimeScaling = 1;
	}
}
