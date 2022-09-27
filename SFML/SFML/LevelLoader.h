// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelLoader.h 
// Description  : LevelLoader Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once

enum class LEVELS
{
	UNASSIGNED = 0,

	MAINMENU,
	LEVELONE,
	LEVELTWO,
	LEVELTHREE
};

class Level;
class LevelLoader
{
public:
	/// <summary>
	/// Calls pollEvents on the current level if one is active
	/// </summary>
	static void PollEvents();
	/// <summary>
	/// Calls update on the current level if one is active
	/// </summary>
	static void Update();
	/// <summary>
	/// Draws the current level if one is active
	/// </summary>
	static void Draw();
	
	/// <summary>
	/// Reloads the current level if one is active
	/// </summary>
	static void ReloadCurrentLevel();
	/// <summary>
	/// Marks the specified level to be loaded at the end of the frame
	/// </summary>
	/// <param name="_level"></param>
	static void LoadLevel(LEVELS _level);
	/// <summary>
	/// Loads the next level in the sequence e.g LevelOne -> LevelTwo
	/// </summary>
	static void LoadNextLevel();
	/// <summary>
	/// Cleans up the current level and creates the pending level
	/// </summary>
	static void ChangeLevelIfLoaded();
	/// <summary>
	/// Cleans up the current level
	/// </summary>
	static void CleanupLevel();

	/// <summary>
	/// Calls ResetCameraReturnDelay on the current level if one is active
	/// </summary>
	static void ResetCameraReturnDelay();

private:
	static Level* m_CurrentLevel;
	static LEVELS m_LevelToLoad;
	static LEVELS m_CurrentLevelID;

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	static float* GetScore();
	static LEVELS GetCurrentLevelID();
};

