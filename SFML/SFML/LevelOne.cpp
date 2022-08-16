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
	for (auto& object : Statics)
	{
		if (object)
			delete object;
		object = nullptr;
	}
	for (auto& object : Birds)
	{
		if (object)
			delete object;
		object = nullptr;
	}
	for (auto& object : Pigs)
	{
		if (object)
			delete object;
		object = nullptr;
	}
	for (auto& object : Destructables)
	{
		if (object)
			delete object;
		object = nullptr;
	}
	for (auto& object : CollisionLess)
	{
		if (object)
			delete object;
		object = nullptr;
	}

	if (m_World)
		delete m_World;
	m_World = nullptr;
}

void LevelOne::PollEvents()
{
	if (Statics::EventHandler.type == sf::Event::MouseButtonPressed)
	{
		m_Catapult.LoadBird(*Birds.back());
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

	for (auto& object : Statics)
	{
		object->Update();
	}
	for (auto& object : Birds)
	{
		object->Update();
	}
	for (auto& object : Pigs)
	{
		object->Update();
	}
	for (auto& object : Destructables)
	{
		object->Update();
	}
	for (auto& object : CollisionLess)
	{
		object->Update();
	}
}

void LevelOne::Draw()
{
	for (auto& object : CollisionLess)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : Statics)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : Destructables)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : Pigs)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : Birds)
	{
		Statics::RenderWindow.draw(*object);
	}

	Statics::RenderWindow.draw(m_Catapult);
}

void LevelOne::CreateCollisionLess()
{
	CollisionLess.emplace_back(new GameObject(*m_World, { 1280 / 2,720 / 2 }));
	CollisionLess.back()->SetTexture("Background.jpg");
	CollisionLess.back()->SetScale({ 2.65f,2.65f });
}

void LevelOne::CreateStatics()
{
	Statics.emplace_back(new GameObject(*m_World, { -62,706 }));
	Statics.emplace_back(new GameObject(*m_World, { 62 * 3,706 }));

	Statics.emplace_back(new GameObject(*m_World, { 62 * 7,706 + 80 }));
	Statics.emplace_back(new GameObject(*m_World, { 62 * 11,706 + 80 }));
	Statics.emplace_back(new GameObject(*m_World, { 62 * 15,706 }));
	Statics.emplace_back(new GameObject(*m_World, { 62 * 19,706 }));
	for (auto& floor : Statics)
	{
		floor->SetTexture("Dirt.png");
	}

	for (auto& object : Statics)
	{
		object->SetBodyType(b2_staticBody);
		object->CreateBody();
	}
}

void LevelOne::CreateBirds()
{
	Birds.emplace_back(new Bird(*m_World, { 30,566 }));
	Birds.emplace_back(new Bird(*m_World, { 70,566 }));
	Birds.emplace_back(new Bird(*m_World, { 110,566 }));
	Birds.emplace_back(new Bird(*m_World, { 150,566 }));
	Birds.emplace_back(new Bird(*m_World, { 190,566 }));
	for (auto& bird : Birds)
	{
		bird->SetTexture("Bird.png");
		bird->SetScale({ 0.25f,0.25f });
		bird->SetShapeType(new b2CircleShape());
	}

	for (auto& object : Birds)
	{
		object->SetBodyType(b2_dynamicBody);
	}
}

void LevelOne::CreatePigs()
{
	Pigs.emplace_back(new GameObject(*m_World, { 1000,566 }));
	Pigs.emplace_back(new GameObject(*m_World, { 1050,566 }));
	Pigs.emplace_back(new GameObject(*m_World, { 1100,566 }));

	for (auto& pig : Pigs)
	{
		pig->SetTexture("Bird.png");
		pig->SetScale({ 0.25f,0.25f });
		pig->SetShapeType(new b2CircleShape());
	}

	for (auto& pig : Pigs)
	{
		pig->SetBodyType(b2_dynamicBody);
		pig->CreateBody();
	}
}

void LevelOne::CreateDestructables()
{
	for (auto& object : Destructables)
	{
		object->SetBodyType(b2_dynamicBody);
		object->CreateBody();
	}
}
