#pragma once
#include <SFML/Audio.hpp>
#include "ContactListener.h"
#include "Utility.h"
#include "Catapult.h"
#include "Level.h"
#include "Pig.h"
#include "Destructable.h"

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
	void CreateJoints();

	void CleanupDestroyedGameObjects(std::vector <GameObject*>& _vector);
	void CleanupDestroyedPigs(std::vector <Pig*>& _vector);
	void CleanupDestroyedBirds(std::vector <Bird*>& _vector);
	void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector);

	b2World* m_World;
	ContactListener m_ContactListener;
	Catapult m_Catapult{ { 225.0f, 520.0f } };

	std::vector<GameObject*> m_CollisionLess{};
	std::vector<GameObject*> m_Statics{};
	std::vector<Bird*> m_Birds{};
	std::vector<Pig*> m_Pigs{};
	std::vector<Destructable*> m_Destructables{};
};