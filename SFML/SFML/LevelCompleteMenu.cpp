#include "LevelCompleteMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Math.h"
#include "LevelLoader.h"

LevelCompleteMenu::LevelCompleteMenu()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("DullBackground",
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"),
			ScreenCentre
		});
	
	GUI::GetInstance().CreateImage("Background",
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"),
			ScreenCentre,
			{1.5f,1.5f}
		});

	GUI::GetInstance().CreateImage("Star1",
		{
			&TextureLoader::LoadTexture("GUI/Star.png"),
			{ScreenCentre.x - 75, ScreenCentre.y - 100},
			{1.2f,1.2f},
			45.0f
		});

	GUI::GetInstance().CreateImage("Star2",
		{
			&TextureLoader::LoadTexture("GUI/Star.png"),
			{ScreenCentre.x, ScreenCentre.y - 110},
			{1.5f,1.5f}
		});

	GUI::GetInstance().CreateImage("Star3",
		{
			&TextureLoader::LoadTexture("GUI/Star.png"),
			{ScreenCentre.x + 75, ScreenCentre.y - 100},
			{1.2f,1.2f},
			-45.0f
		});

	GUI::GetInstance().CreateText("Score",
		{
			{ScreenCentre.x, ScreenCentre.y - 20},
			"Score: " + FloatToString(*LevelLoader::GetScore(),0),

		});

	CreateButtons();

	SetStarsBasedOnScore();
}

LevelCompleteMenu::~LevelCompleteMenu()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("Score");
	GUI::GetInstance().CleanupButtonElement("Continue");
	GUI::GetInstance().CleanupButtonElement("Retry");
}

void LevelCompleteMenu::SetStarsBasedOnScore()
{
	float totalScore = *LevelLoader::GetScore();

	switch (LevelLoader::GetCurrentLevelID())
	{
	case LEVELS::LEVELONE:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (*LevelLoader::GetScore() >= 35000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (*LevelLoader::GetScore() >= 60000)
		{
			GUI::GetInstance().GetImage("Star3").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		break;
	}
	case LEVELS::LEVELTWO:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (*LevelLoader::GetScore() >= 55000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (*LevelLoader::GetScore() >= 70000)
		{
			GUI::GetInstance().GetImage("Star3").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		break;
	}
	case LEVELS::LEVELTHREE:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (*LevelLoader::GetScore() >= 50000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (*LevelLoader::GetScore() >= 70000)
		{
			GUI::GetInstance().GetImage("Star3").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		break;
	}
	default:
		break;
	}
}

void LevelCompleteMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Continue",
		{
			"Continue",
			{ ScreenCentre.x,ScreenCentre.y + 60},
			{1,1},
			[]()
			{
				LevelLoader::LoadNextLevel();
			}
		});
	GUI::GetInstance().CreateButton("Retry",
		{
			"Retry",
			{ ScreenCentre.x,ScreenCentre.y + 130},
			{1,1},
			[]()
			{
				LevelLoader::ReloadCurrentLevel();
			}
		});
}
