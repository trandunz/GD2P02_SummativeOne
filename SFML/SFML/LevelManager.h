#pragma once
#include "MainMenu.h"

class LevelManager
{
public:
	static Level* CurrentLevel;
	static void LoadLevel(Level* _level);
	static void CleanupLevel();
};

