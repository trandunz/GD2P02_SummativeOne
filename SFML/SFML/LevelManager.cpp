#include "LevelManager.h"

Level* LevelManager::CurrentLevel = nullptr;

void LevelManager::LoadLevel(Level* _level)
{
	CleanupLevel();
	CurrentLevel = _level;
}

void LevelManager::CleanupLevel()
{
	if (CurrentLevel)
		delete CurrentLevel;
	CurrentLevel = nullptr;
}
