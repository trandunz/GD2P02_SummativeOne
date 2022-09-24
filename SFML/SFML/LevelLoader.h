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
	static void PollEvents();
	static void Update();
	static void Draw();
	
	static void ReloadCurrentLevel();
	static void LoadLevel(LEVELS _level);
	static void LoadNextLevel();
	static void ChangeLevelIfLoaded();
	static void CleanupLevel();

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

