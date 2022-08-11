#include "Level.h"

Level::Level()
{
	World = new b2World({ 0,10.0f });

	CreateStaticBodys();
	CreateDynamicBodys();
}

Level::~Level()
{
	for (auto& object : DynamicObjects)
	{
		if (object)
			delete object;
		object = nullptr;
	}
	for (auto& object : StaticObjects)
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
		m_Catapult.LoadBird(*DynamicObjects.back());
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

	for (auto& object : StaticObjects)
	{
		object->Update();
	}
	for (auto& object : DynamicObjects)
	{
		object->Update();
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& object : StaticObjects)
	{
		target.draw(*object);
	}
	for (auto& object : DynamicObjects)
	{
		target.draw(*object);
	}

	target.draw(m_Catapult);
}

void Level::CreateStaticBodys()
{
	StaticObjects.emplace_back(new GameObject(*World, { 600,550 }));
	StaticObjects.back()->SetTexture("Ground.png");

	for (auto& object : StaticObjects)
	{
		object->SetBodyType(b2_staticBody);
	}
}

void Level::CreateDynamicBodys()
{
	for (int i = 0; i < 3; i++)
	{
		DynamicObjects.emplace_back(new GameObject(*World, { 200 + (200 * (float)i),100 }));
	}

	for (auto& object : DynamicObjects)
	{
		object->SetBodyType(b2_dynamicBody);
	}
}
