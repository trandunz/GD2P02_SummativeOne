#include "LevelLoader.h"
#include "Level.h"
#include "MainMenu.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"

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

void LevelLoader::LoadNextLevel()
{
	switch (m_CurrentLevelID)
	{
	case LEVELS::MAINMENU:
	{
		m_LevelToLoad = LEVELS::LEVELONE;
		break;
	}
	case LEVELS::LEVELONE:
	{
		m_LevelToLoad = LEVELS::LEVELTWO;
		break;
	}
	case LEVELS::LEVELTWO:
	{
		m_LevelToLoad = LEVELS::LEVELTHREE;
		break;
	}
	case LEVELS::LEVELTHREE:
	{
		m_LevelToLoad = LEVELS::MAINMENU;
		break;
	}
	default:
		break;
	}
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
		case LEVELS::LEVELTWO:
		{
			m_CurrentLevel = new LevelTwo;
			break;
		}
		case LEVELS::LEVELTHREE:
		{
			m_CurrentLevel = new LevelThree;
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

void LevelLoader::ResetCameraReturnDelay()
{
	if (m_CurrentLevel)
	{
		GameLevel* gameLevel = dynamic_cast<GameLevel*>(m_CurrentLevel);
		if (gameLevel)
		{
			gameLevel->ResetCameraReturnDelay();
		}
	}
}

float* LevelLoader::GetScore()
{
	if (m_CurrentLevel)
	{
		GameLevel* gameLevel = dynamic_cast<GameLevel*>(m_CurrentLevel);
		if (gameLevel)
		{
			return &gameLevel->GetScore();
		}
	}
	else
	{
		return {};
	}
}

LEVELS LevelLoader::GetCurrentLevelID()
{
	return m_CurrentLevelID;
}
