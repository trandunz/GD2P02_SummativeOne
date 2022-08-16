#pragma once
#include <SFML/Audio.hpp>
#include "ContactListener.h"
#include "Statics.h"
#include "Catapult.h"
#include "GameObject.h"
#include "Level.h"

class LevelOne : public Level
{
public:
	LevelOne();
	virtual ~LevelOne();

	virtual void PollEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void CreateCollisionLess();
	void CreateStatics();
	void CreateBirds();
	void CreatePigs();
	void CreateDestructables();

	b2World* m_World;
	ContactListener m_ContactListener;
	Catapult m_Catapult{ { 225.0f, 520.0f } };
	std::vector<GameObject*> CollisionLess{};
	std::vector<GameObject*> Statics{};
	std::vector<GameObject*> Birds{};
	std::vector<GameObject*> Pigs{};
	std::vector<GameObject*> Destructables{};
};

