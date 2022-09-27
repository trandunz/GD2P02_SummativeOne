// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelFailedMenu.h 
// Description  : LevelFailedMenu Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once

class LevelFailedMenu
{
public:
	/// <summary>
	/// LevelFailedMenu Constructor
	/// </summary>
	LevelFailedMenu();
	/// <summary>
	/// LevelFailedMenu Destructor
	/// </summary>
	~LevelFailedMenu();

private:
	/// <summary>
	/// Creates the background for the menu
	/// </summary>
	void CreateMenuBackground();
	/// <summary>
	/// Handles creation of menu buttons
	/// </summary>
	void CreateButtons();
	/// <summary>
	/// Handles creation of menu text (e.g score)
	/// </summary>
	void CreateText();
};

