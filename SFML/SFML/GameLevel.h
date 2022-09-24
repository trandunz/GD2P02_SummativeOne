// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: GameLevel.h 
// Description  : GameLevel Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "ContactListener.h"
#include "Utility.h"
#include "Catapult.h"
#include "Level.h"
#include "Pig.h"
#include "Destructable.h"


class PauseMenu;
class LevelCompleteMenu;
class LevelFailedMenu;
class GameLevel :
    public Level
{
public:
	GameLevel();
	/// <summary>
	/// GameLevel Destructor
	/// </summary>
	virtual ~GameLevel();

	virtual void PollEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

	void ResetCameraReturnDelay();

protected:
	void TogglePause();

	virtual void CreateCollisionLess();
	virtual void CreateStatics();
	virtual void CreateBirds();
	virtual void CreatePigs();
	virtual void CreateDestructables();
	virtual void CreateJoints();

	void CleanupDestroyedGameObjects(std::vector <GameObject*>& _vector);
	void CleanupDestroyedPigs(std::vector <Pig*>& _vector);
	void CleanupDestroyedBirds(std::vector <Bird*>& _vector);
	virtual void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector);

	float m_CameraDelayTimer{ 0.0f };
	float m_CameraReturnDelay{ 1.5f };
	float m_Score{ 0.0f };

	sf::View m_View;
	b2World* m_World{ nullptr };
	ContactListener m_ContactListener{};
	Catapult m_Catapult{ { 225.0f, 520.0f } };

	sf::Vector2f m_CameraStartPos{};
	sf::Vector2f m_CameraTargetPos{};
	bool m_LerpRight{ true };
	float m_CameraLerpAmount{};
	float m_FireTimer{};
	float m_FireTime{ 3.0f };

	bool m_LevelComplete{ false };

	PauseMenu* m_PauseMenu{ nullptr };
	LevelCompleteMenu* m_LevelCompleteMenu{ nullptr };
	LevelFailedMenu* m_LevelFailedMenu{ nullptr };

	std::vector<GameObject*> m_CollisionLess{};
	std::vector<GameObject*> m_Statics{};
	std::vector<Bird*> m_Birds{};
	std::vector<Pig*> m_Pigs{};
	std::vector<Destructable*> m_Destructables{};

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	float& GetScore();
};

