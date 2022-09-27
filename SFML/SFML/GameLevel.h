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
#include "Level.h"
#include "ContactListener.h"
#include "Catapult.h"

#define VELOCITY_ITERATIONS 10
#define POSITION_ITERATIONS 10

class Catapult;
class Pig;
class Destructable;
class PauseMenu;
class LevelCompleteMenu;
class LevelFailedMenu;
class GameLevel : public Level
{
public:
	/// <summary>
	/// GameLevel Constructor
	/// </summary>
	GameLevel();
	/// <summary>
	/// GameLevel Destructor
	/// </summary>
	virtual ~GameLevel();

	/// <summary>
	/// Handles all sfml events such as mouse pressed
	/// </summary>
	virtual void PollEvents() override;
	/// <summary>
	/// Handles updating everything in the scene
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// Handles drawing everything in the scene
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// Resets the cameraReturn timer do the camera stays looking at the destructables for longer
	/// </summary>
	void ResetCameraReturnDelay();

protected:
	/// <summary>
	/// Pause / Resume the game
	/// </summary>
	void TogglePause();

	/// <summary>
	/// Handles the creation of all collisionless objects
	/// </summary>
	virtual void CreateCollisionLess();
	/// <summary>
	/// Handles the creation of all static objects
	/// </summary>
	virtual void CreateStatics();
	/// <summary>
	/// Handles the creation of all birds
	/// </summary>
	virtual void CreateBirds();
	/// <summary>
	/// Handles the creation of all pigs
	/// </summary>
	virtual void CreatePigs();
	/// <summary>
	/// Handles the creation of all Destructables
	/// </summary>
	virtual void CreateDestructables();
	/// <summary>
	/// Handles the creation of all Joints
	/// </summary>
	virtual void CreateJoints();

	/// <summary>
	/// Cleans up all gameobjects marked for destroy
	/// </summary>
	/// <param name="_vector"></param>
	void CleanupDestroyedGameObjects(std::vector <GameObject*>& _vector);
	/// <summary>
	/// Cleans up all pigs marked for destroy
	/// </summary>
	/// <param name="_vector"></param>
	void CleanupDestroyedPigs(std::vector <Pig*>& _vector);
	/// <summary>
	/// Cleans up all Birds marked for destroy
	/// </summary>
	/// <param name="_vector"></param>
	void CleanupDestroyedBirds(std::vector <Bird*>& _vector);
	/// <summary>
	/// Cleans up all Destructables marked for destroy
	/// </summary>
	/// <param name="_vector"></param>
	virtual void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector);

	/// <summary>
	/// Handles creation of GUI elements
	/// </summary>
	void CreateGUIElements();

	/// <summary>
	/// Cleans up any objects and joints that are marked for destroy
	/// </summary>
	void  HandleGarbageCollection();

	/// <summary>
	/// Handles all the camera pan / lerp logic. Made to be called every frame.
	/// </summary>
	void CameraPanUpdate();

	/// <summary>
	/// Creates level complete / failed menu depending on if you win or loose
	/// </summary>
	void HandleWinLossConditions();

	/// <summary>
	/// Updates the score GUI element with the current score value
	/// </summary>
	void UpdateLevelScoreGUI();

	float m_CameraDelayTimer{};
	float m_CameraReturnDelay{ 1.5f };
	float m_Score{};

	sf::View m_View{};
	b2World* m_World{ nullptr };
	ContactListener m_ContactListener{};
	Catapult m_Catapult{ { 225.0f, 520.0f } };

	sf::Vector2f m_CameraStartPos{};
	sf::Vector2f m_CameraTargetPos{};
	bool m_LerpRight{ true };
	float m_CameraLerpAmount{};
	float m_FireTime{ 3.0f };
	float m_FireTimer{ m_FireTime };

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

