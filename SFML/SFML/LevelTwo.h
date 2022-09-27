// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelTwo.h 
// Description  : LevelTwo Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameLevel.h"

class LevelTwo : public GameLevel
{
public:
	/// <summary>
	/// LevelTwo Constructor
	/// </summary>
	LevelTwo();
	/// <summary>
	/// LevelTwo Destructor
	/// </summary>	
	virtual ~LevelTwo();

protected:
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
};