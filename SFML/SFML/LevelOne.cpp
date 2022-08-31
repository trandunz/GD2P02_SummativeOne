#include "LevelOne.h"
#include "AudioManager.h"
#include "JointManager.h"

LevelOne::LevelOne()
{
	AudioManager::StopMusic();
	m_World = new b2World({ 0,10.0f });
	m_World->SetContactListener(&m_ContactListener);
	JointManager::GetInstance().SetWorld(*m_World);
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
	CreateJoints();
}

LevelOne::~LevelOne()
{
	JointManager::GetInstance().ForceCleanupJoints();
	CleanupVector(m_Statics);
	CleanupVector(m_CollisionLess);
	CleanupVector(m_Birds);
	CleanupVector(m_Pigs);
	CleanupVector(m_Destructables);
	

	if (m_World)
		delete m_World;
	m_World = nullptr;
}

void LevelOne::PollEvents()
{
	if (Statics::EventHandler.type == sf::Event::MouseButtonPressed)
	{
		m_Catapult.LoadBird(*m_Birds.back());
	}

	if (Statics::EventHandler.type == sf::Event::MouseButtonReleased)
	{
		m_Catapult.ReleaseBird();
	}

	if (Statics::EventHandler.type == sf::Event::MouseMoved)
	{
		m_Catapult.MoveBird();
	}
}

void LevelOne::Update()
{
	m_World->Step(1 / 60.0f, 10, 10);

	for (auto& staticObject : m_Statics)
	{
		staticObject->Update();
	}
	for (auto& bird : m_Birds)
	{
		bird->Update();
	}
	for (auto& pig : m_Pigs)
	{
		pig->Update();
	}
	for (auto& destructable : m_Destructables)
	{
		destructable->Update();
	}
	for (auto& collisionLess : m_CollisionLess)
	{
		collisionLess->Update();
	}

	CleanupDestroyedGameObjects(m_Statics);
	CleanupDestroyedDestructables(m_Destructables);
	CleanupDestroyedGameObjects(m_CollisionLess);
	CleanupDestroyedPigs(m_Pigs);
	CleanupDestroyedBirds(m_Birds);
	JointManager::GetInstance().CleanupMarkedJoints();
}

void LevelOne::Draw()
{
	for (auto& object : m_CollisionLess)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Statics)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Destructables)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Pigs)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Birds)
	{
		Statics::RenderWindow.draw(*object);
	}

	Statics::RenderWindow.draw(m_Catapult);
}

void LevelOne::CreateCollisionLess()
{
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 1280 / 2,720 / 2 }));
	m_CollisionLess.back()->SetTexture("Background.jpg");
	m_CollisionLess.back()->SetScale({ 2.65f,2.65f });
}

void LevelOne::CreateStatics()
{
	m_Statics.emplace_back(new GameObject(*m_World, { -62,706 }));
	m_Statics.emplace_back(new GameObject(*m_World, { 62 * 3,706 }));

	m_Statics.emplace_back(new GameObject(*m_World, { 62 * 7,706 + 80 }));
	m_Statics.emplace_back(new GameObject(*m_World, { 62 * 11,706 + 80 }));
	m_Statics.emplace_back(new GameObject(*m_World, { 62 * 15,706 }));
	m_Statics.emplace_back(new GameObject(*m_World, { 62 * 19,706 }));
	for (auto& floor : m_Statics)
	{
		floor->SetTexture("Dirt.png");
	}

	for (auto& object : m_Statics)
	{
		object->SetBodyType(b2_staticBody);
		object->CreateBody();
	}
}

void LevelOne::CreateBirds()
{
	m_Birds.emplace_back(new Bird(*m_World, { 30,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 70,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 110,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 150,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 190,566 }));

	for (auto& bird : m_Birds)
	{
		bird->SetTexture("Bird.png");
		bird->SetScale({ 0.25f,0.25f });
		bird->SetShapeType(new b2CircleShape());
	}

	for (auto& object : m_Birds)
	{
		object->SetBodyType(b2_dynamicBody);
	}
}

void LevelOne::CreatePigs()
{
	m_Pigs.emplace_back(new Pig(*m_World, { 950,350 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1050,350 }));

	for (auto& pig : m_Pigs)
	{
		pig->SetTexture("Bird.png");
		pig->SetScale({ 0.25f,0.25f });
		pig->SetShapeType(new b2CircleShape());
	}

	for (auto& pig : m_Pigs)
	{
		pig->SetBodyType(b2_dynamicBody);
		pig->CreateBody();
	}
}

void LevelOne::CreateDestructables()
{
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000,400 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 400 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
}

void LevelOne::CreateJoints()
{
	b2DistanceJointDef distanceJoint{};
	distanceJoint.bodyA = m_Destructables[0]->GetBody();
	distanceJoint.bodyB = m_Destructables[1]->GetBody();
	distanceJoint.collideConnected = false;
	distanceJoint.length = 0.0f;
	distanceJoint.minLength = 0.0f;
	distanceJoint.maxLength = 0.0f;
	
	JointManager::GetInstance().CreateDistanceJoint(distanceJoint);
}

void LevelOne::CleanupDestroyedGameObjects(std::vector<GameObject*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void LevelOne::CleanupDestroyedPigs(std::vector<Pig*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void LevelOne::CleanupDestroyedBirds(std::vector<Bird*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void LevelOne::CleanupDestroyedDestructables(std::vector<Destructable*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}
