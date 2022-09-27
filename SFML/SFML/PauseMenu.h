// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PauseMenu.h 
// Description  : PauseMenu Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
class PauseMenu
{
public:
	PauseMenu();
	/// <summary>
	/// PauseMenu Destructor
	/// </summary>
	~PauseMenu();

private:
	/// <summary>
	/// Handles creation of menu buttons
	/// </summary>
	void CreateButtons();
	/// <summary>
	/// Handles creation of menu text
	/// </summary>
	void CreateText();
	/// <summary>
	/// Creates the background for the menu
	/// </summary>
	void CreateMenuBackground();
};

