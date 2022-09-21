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
	static float* GetScore();
	static LEVELS GetCurrentLevelID();
private:
	static Level* m_CurrentLevel;
	static LEVELS m_LevelToLoad;
	static LEVELS m_CurrentLevelID;
};

