// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelOne.h 
// Description  : LevelOne Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameLevel.h"

class LevelOne : public GameLevel
{
public:
	LevelOne();
	/// <summary>
	/// LevelOne Destructor
	/// </summary>	
	virtual ~LevelOne();

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;
};