#include "LevelLoader.h"
#include "Level.h"


Level* LevelLoader::CurrentLevel = nullptr;

void LevelLoader::PollEvents()
{
	if (CurrentLevel != nullptr)
		CurrentLevel->PollEvents();
}

void LevelLoader::Update()
{
	if (CurrentLevel != nullptr)
		CurrentLevel->Update();
}

void LevelLoader::Draw()
{
	if (CurrentLevel != nullptr)
		CurrentLevel->Draw();
}

void LevelLoader::LoadLevel(Level* _level)
{
	CleanupLevel();
	CurrentLevel = _level;
}

void LevelLoader::CleanupLevel()
{
	if (CurrentLevel)
		delete CurrentLevel;
	CurrentLevel = nullptr;
}
