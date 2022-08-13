#pragma once
#include "Helper.h"
#include "Catapult.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

class Level : public sf::Drawable
{
public:
	Level();
	virtual ~Level();

	virtual void PollEvents(sf::Event& _event);
	virtual void Update();

	b2World* World;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void CreateCollisionLess();
	void CreateStatics();
	void CreateBirds();
	void CreatePigs();
	void CreateDestructables();

	Catapult m_Catapult{ { 225.0f, 520.0f } };
	std::vector<GameObject*> CollisionLess{};
	std::vector<GameObject*> Statics{};
	std::vector<GameObject*> Birds{};
	std::vector<GameObject*> Pigs{};
	std::vector<GameObject*> Destructables{};
};

