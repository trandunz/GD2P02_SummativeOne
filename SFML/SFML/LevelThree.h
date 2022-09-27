// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelThree.h 
// Description  : LevelThree Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameLevel.h"

class LevelThree : public GameLevel
{
public:
	/// <summary>
	/// LevelThree Constructor
	/// </summary>
	LevelThree();
	/// <summary>
	/// LevelThree Destructor
	/// </summary>	
	virtual ~LevelThree();

	/// <summary>
	/// Handles updating everything in the scene
	/// </summary>
	void Update() override;
	/// <summary>
	/// Draws everything in the scene
	/// </summary>
	void Draw() override;

protected:
	/// <summary>
	/// Handles the creation of all static objects
	/// </summary>
	virtual void CreateStatics() override;
	/// <summary>
	/// Handles the creation of all birds
	/// </summary>
	virtual void CreateBirds() override;
	/// <summary>
	/// Handles the creation of all pigs
	/// </summary>
	virtual void CreatePigs() override;
	/// <summary>
	/// Handles the creation of all Destructables
	/// </summary>
	virtual void CreateDestructables() override;
	/// <summary>
	/// Handles the creation of all Joints
	/// </summary>
	virtual void CreateJoints() override;

	/// <summary>
	/// Cleans up all Destructables marked for destroy, including pulleyBlockA and pulleyBlockB
	/// </summary>
	/// <param name="_vector"></param>
	void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector) override;

private:
	sf::VertexArray m_PulleyJointRope{ sf::LinesStrip };
	Destructable* m_PulleyBlockA{ nullptr };
	Destructable* m_PulleyBlockB{ nullptr };
};

