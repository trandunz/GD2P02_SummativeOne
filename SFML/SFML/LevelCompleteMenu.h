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

class LevelCompleteMenu
{
public:
	/// <summary>
	/// LevelCompleteMenu Constructor
	/// </summary>
	LevelCompleteMenu();
	/// <summary>
	/// LevelCompleteMenu Destructor
	/// </summary>
	~LevelCompleteMenu();

private:
	/// <summary>
	/// Creates the background for the menu
	/// </summary>
	void CreateMenuBackground();
	/// <summary>
	/// Creeates the three star GUI images
	/// </summary>
	void CreateStarImages();
	/// <summary>
	/// Updates the number of starts based on the score value for that level
	/// </summary>
	void SetStarTexturesBasedOnScore();
	/// <summary>
	/// Handles creation of menu buttons
	/// </summary>
	void CreateButtons();
	/// <summary>
	/// Handles creation of menu text (e.g score)
	/// </summary>
	void CreateText();
};

