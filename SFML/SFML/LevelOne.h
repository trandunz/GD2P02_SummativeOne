#pragma once
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

	static void ResetCameraReturnDelay();
	static float& GetScore();
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

	static float m_CameraDelayTimer;
	static float m_CameraReturnDelay;

	sf::View m_View;
	b2World* m_World{nullptr};
	ContactListener m_ContactListener{};
	Catapult m_Catapult{ { 225.0f, 520.0f } };

	int m_NextBirdIndex{ 0 };
	sf::Vector2f m_CameraStartPos{};
	sf::Vector2f m_CameraTargetPos{};
	bool m_LerpRight{true};
	float m_CameraLerpAmount{};
	float m_FireTimer{};
	float m_FireTime{3.0f};

	

	std::vector<GameObject*> m_CollisionLess{};
	std::vector<GameObject*> m_Statics{};
	std::vector<Bird*> m_Birds{};
	std::vector<Pig*> m_Pigs{};
	std::vector<Destructable*> m_Destructables{};
};