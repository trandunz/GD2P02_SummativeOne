// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelCompleteMenu.h 
// Description  : LevelCompleteMenu Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Button.h"
class LevelCompleteMenu
{
public:
	LevelCompleteMenu();
	/// <summary>
	/// LevelCompleteMenu Destructor
	/// </summary>
	~LevelCompleteMenu();

private:
	void SetStarsBasedOnScore();
	void CreateButtons();
};

