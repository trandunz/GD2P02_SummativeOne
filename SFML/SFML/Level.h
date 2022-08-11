#pragma once
#include "Helper.h"
#include "Catapult.h"
#include "GameObject.h"

class Level : public sf::Drawable
{
public:
	Level();
	~Level();

	void PollEvents(sf::Event& _event);
	void Update();

	b2World* World;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void CreateStaticBodys();
	void CreateDynamicBodys();

	Catapult m_Catapult{ { 200.0f, 450.0f } };
	std::vector<GameObject*> StaticObjects{};
	std::vector<GameObject*> DynamicObjects{};
};

