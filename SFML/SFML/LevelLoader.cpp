#include "LevelLoader.h"
#include "Level.h"
#include "MainMenu.h"
#include "LevelOne.h"

Level* LevelLoader::m_CurrentLevel = nullptr;
LEVELS LevelLoader::m_LevelToLoad = LEVELS::UNASSIGNED;
LEVELS LevelLoader::m_CurrentLevelID = LEVELS::UNASSIGNED;

void LevelLoader::PollEvents()
{
	if (m_CurrentLevel != nullptr)
		m_CurrentLevel->PollEvents();
}

void LevelLoader::Update()
{
	if (m_CurrentLevel != nullptr)
		m_CurrentLevel->Update();
}

void LevelLoader::Draw()
{
	if (m_CurrentLevel != nullptr)
		m_CurrentLevel->Draw();
}

void LevelLoader::ReloadCurrentLevel()
{
	m_LevelToLoad = m_CurrentLevelID;
}

void LevelLoader::LoadLevel(LEVELS _level)
{
	m_LevelToLoad = _level;
}

void LevelLoader::ChangeLevelIfLoaded()
{
	if (m_LevelToLoad != LEVELS::UNASSIGNED)
	{
		CleanupLevel();
		m_CurrentLevelID = m_LevelToLoad;
		switch (m_LevelToLoad)
		{
		case LEVELS::MAINMENU:
		{
			m_CurrentLevel = new MainMenu;
			break;
		}
		case LEVELS::LEVELONE:
		{
			m_CurrentLevel = new LevelOne;
			break;
		}
		default:
			break;
		}
		m_LevelToLoad = LEVELS::UNASSIGNED;
	}
}

void LevelLoader::CleanupLevel()
{
	if (m_CurrentLevel)
		delete m_CurrentLevel;
	m_CurrentLevel = nullptr;
}
