#include "LevelOne.h"
#include "AudioManager.h"

LevelOne::LevelOne()
{
	AudioManager::StopMusic();
	m_World = new b2World({ 0,10.0f });
	m_World->SetContactListener(&m_ContactListener);
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
}

LevelOne::~LevelOne()
{
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

	for (auto& object : m_Statics)
	{
		object->Update();
	}
	for (auto& object : m_Birds)
	{
		object->Update();
	}
	for (auto& object : m_Pigs)
	{
		object->Update();
	}
	for (auto& object : m_Destructables)
	{
		object->Update();
	}
	for (auto& object : m_CollisionLess)
	{
		object->Update();
	}

	CleanupDestroyedGameObjects(m_Statics);
	CleanupDestroyedDestructables(m_Destructables);
	CleanupDestroyedGameObjects(m_CollisionLess);
	CleanupDestroyedPigs(m_Pigs);
	CleanupDestroyedBirds(m_Birds);
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
	m_Pigs.emplace_back(new Pig(*m_World, { 1000,566 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1050,566 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1100,566 }));

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
	m_Destructables.emplace_back(new Destructable(*m_World, { 1050,566 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1050,500 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1050,500 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
}
