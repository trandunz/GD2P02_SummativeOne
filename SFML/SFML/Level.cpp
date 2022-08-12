#include "Level.h"

Level::Level()
{
	World = new b2World({ 0,10.0f });
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
}

Level::~Level()
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

	if (World)
		delete World;
	World = nullptr;
}

void Level::PollEvents(sf::Event& _event)
{
	if (_event.type == sf::Event::MouseButtonPressed)
	{
		//m_Catapult.LoadBird(*Statics.back());
	}

	if (_event.type == sf::Event::MouseButtonReleased)
	{
		m_Catapult.ReleaseBird();
	}

	if (_event.type == sf::Event::MouseMoved)
	{
		m_Catapult.MoveBird();
	}
}

void Level::Update()
{
	World->Step(1 / 60.0f, 6, 2);

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

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& object : Statics)
	{
		target.draw(*object);
	}
	for (auto& object : Destructables)
	{
		target.draw(*object);
	}
	for (auto& object : Pigs)
	{
		target.draw(*object);
	}
	for (auto& object : Birds)
	{
		target.draw(*object);
	}
	for (auto& object : CollisionLess)
	{
		target.draw(*object);
	}

	target.draw(m_Catapult);
}

void Level::CreateCollisionLess()
{
}

void Level::CreateStatics()
{
	for (auto& object : Statics)
	{
		object->SetBodyType(b2_staticBody);
		object->CreateBody();
	}
}

void Level::CreateBirds()
{
	for (auto& object : Birds)
	{
		object->SetBodyType(b2_dynamicBody);
	}
}

void Level::CreatePigs()
{
	for (auto& object : Pigs)
	{
		object->SetBodyType(b2_dynamicBody);
		object->CreateBody();
	}
}

void Level::CreateDestructables()
{
	for (auto& object : Destructables)
	{
		object->SetBodyType(b2_dynamicBody);
		object->CreateBody();
	}
}
