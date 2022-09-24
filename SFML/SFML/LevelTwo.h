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
	LevelTwo();
	/// <summary>
	/// LevelTwo Destructor
	/// </summary>	
	virtual ~LevelTwo();

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;
};