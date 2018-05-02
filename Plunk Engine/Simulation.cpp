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

	/*for (int i = 0; i < 25; i++)
	{
		Entity entity("sphere");
		entity.AddComponent(RigidBodySphere(glm::vec3(GenerateRandomNum(-8, 8), GenerateRandomNum(3, 10), GenerateRandomNum(-8, 8)), 0.5f));
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Sphere));
		entity.AddComponent(ComponentModel(std::string("models/primitives/icosphere/icosphere4.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}*/

	for (int i = 0; i < 1; i++)
	{
		Entity entity("sphereBig");
		RigidBodySphere body = RigidBodySphere(glm::vec3(0, 9.81f + 0.5f, 0), 0.5f);
		body.mass = 1;
		body.mApplyGravity = true;
		//body.velocity = glm::vec3(1.f, 0.f, 0.f);

		entity.AddComponent(body);
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Sphere));
		entity.AddComponent(ComponentModel(std::string("models/primitives/icosphere/icosphere5.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}

	for (int i = 0; i < 1; i++)
	{
		Entity entity("cylinder");
		RigidBodyCylinder body = RigidBodyCylinder(glm::vec3(2, 1.f, -20), 2.f, 0.5f);
		body.mApplyGravity = false;
		body.mass = 1000000000000.f;

		entity.AddComponent(body);
		//entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Plane));
		entity.AddComponent(ComponentModel(std::string("models/primitives/cylinder/cylinder256.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}

	Entity DirLight("DirLight");
	DirLight.AddComponent(ComponentDirectionalLight());
	DirLight.AddComponent(ComponentShadowCast());
	entityManager.AddEntity(DirLight);

	for (int i = 0; i < 1; i++)
	{
		Entity entity("plane");
		RigidBodyPlane body = RigidBodyPlane(glm::vec3(0, 0, 0), glm::vec3(0.f));
		body.mApplyGravity = false;
		body.mass = 1000000000000.f;

		entity.AddComponent(body);
		entity.AddComponent(ComponentCollision(ComponentCollision::collisionPrimitiveType::Plane));
		entity.AddComponent(ComponentModel(std::string("models/primitives/plane/quad.obj"), true, false));
		entity.AddComponent(ComponentRenderable());
		glm::vec3 colour(GenerateRandomNum(0, 1), GenerateRandomNum(0, 1), GenerateRandomNum(0, 1));
		entity.AddComponent(ComponentMaterial(colour, colour, glm::vec3(1.0), 64.0f));
		entityManager.AddEntity(entity);
	}
}

Simulation::Simulation(GLFWwindow *const pWindow, const glm::vec3& pStartingPosition) :
	entityManager(EntityManager()),
	inputManager(InputManager()),
	systemManager(SystemManager()),
	systemPhysics(SystemPhysics()),
	systemCollision(SystemCollision()),
	systemShadows(SystemShadows()),
	systemLighting(SystemLighting()),
	systemRender(SystemRender()),
	mCamera(Camera(pStartingPosition)),
	mDeltaTime(0.),
	mCurrentFrame(0.),
	mLastFrame(0.),
	mTimeScaling(1.0),
	mSimulationTime(0.),
	mSimulationPaused(false),
	mRestitutionCoefficient(0.6f),
	scrollWheelSensitivity(0.1f)
{
	systemManager.AddSystem(systemPhysics);
	systemManager.AddSystem(systemCollision);
	systemManager.AddSystem(systemShadows);  // Shadow setting must be performed before render
	systemManager.AddSystem(systemLighting); // Lighting must be performed before render
	systemManager.AddSystem(systemRender);

	inputManager.setInputCallbacks(pWindow, this);
	AddEntitiesToManager(entityManager);
	systemManager.LoadSystems(entityManager, this);

	TogglePauseSimulation();
}

Simulation::~Simulation()
{}

void Simulation::Run()
{
	// Per frame time logic
	mCurrentFrame = glfwGetTime();
	mDeltaTime = mCurrentFrame - mLastFrame;
	mLastFrame = mCurrentFrame;

	if (mDeltaTime > 1.f)
	{
		mDeltaTime = 0.01666666667;
	}

	mDeltaTime *= mTimeScaling;

	if (!mSimulationPaused)
	{
		mSimulationTime += mDeltaTime;
	}

	systemManager.ActionSystems(entityManager);
}

void Simulation::TogglePauseSimulation()
{
	if (mSimulationPaused)
	{
		systemPhysics.mRunning = true;
		systemCollision.mRunning = true;

		mSimulationPaused = false;
		cout << "Simulation unpaused" << endl;
	}
	else
	{
		systemPhysics.mRunning = false;
		systemCollision.mRunning = false;

		mSimulationPaused = true;
		cout << "Simulation paused" << endl;
	}
}

void Simulation::ChangeTimeScaling(double &pAmount)
{
	pAmount *= scrollWheelSensitivity;
	mTimeScaling += pAmount;

	if (mTimeScaling < 0.1f)
	{
		mTimeScaling = 0.1f;
		return;
	}
	else if (mTimeScaling > 1)
	{
		mTimeScaling = 1;
		return;
	}

	cout << "Time scaling changed to = " << mTimeScaling << endl;
}

void Simulation::ChangeRestitution(double & pAmount)
{
	pAmount *= scrollWheelSensitivity;
	mRestitutionCoefficient += pAmount;

	if (mRestitutionCoefficient < 0.1f)
	{
		mRestitutionCoefficient = 0.1f;
		return;
	}
	else if (mRestitutionCoefficient > 1.5f)
	{
		mRestitutionCoefficient = 1.5f;
		return;
	}

	cout << "Restitution changed to = " << mRestitutionCoefficient << endl;
}
