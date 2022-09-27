// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelCompleteMenu.cpp 
// Description  : LevelCompleteMenu Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "LevelCompleteMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Math.h"
#include "LevelLoader.h"

LevelCompleteMenu::LevelCompleteMenu()
{
	CreateMenuBackground();
	CreateStarImages();
	CreateText();
	CreateButtons();

	SetStarTexturesBasedOnScore();
}

LevelCompleteMenu::~LevelCompleteMenu()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("Score");
	GUI::GetInstance().CleanupButtonElement("Continue");
	GUI::GetInstance().CleanupButtonElement("Retry");
}

void LevelCompleteMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("DullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Texture
			ScreenCentre // Position
		});

	GUI::GetInstance().CreateImage("Background", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			ScreenCentre, // Position
			{1.5f,1.5f} // Scale
		});
}

void LevelCompleteMenu::CreateStarImages()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("Star1", // Key
		{
			&TextureLoader::LoadTexture("GUI/Star.png"), // Texture
			{ScreenCentre.x - 75, ScreenCentre.y - 100}, // Position
			{1.2f,1.2f}, // Scale
			45.0f // Rotation (degrees)
		});

	GUI::GetInstance().CreateImage("Star2", // Key
		{
			&TextureLoader::LoadTexture("GUI/Star.png"), // Texture
			{ScreenCentre.x, ScreenCentre.y - 110}, // Position
			{1.5f,1.5f} // Scale
		});

	GUI::GetInstance().CreateImage("Star3", // Key
		{
			&TextureLoader::LoadTexture("GUI/Star.png"), // Texture
			{ScreenCentre.x + 75, ScreenCentre.y - 100}, // Position
			{1.2f,1.2f}, // Scale
			-45.0f // Rotation (degrees)
		});
}

void LevelCompleteMenu::SetStarTexturesBasedOnScore()
{
	float totalScore = *LevelLoader::GetScore();

	switch (LevelLoader::GetCurrentLevelID())
	{
	case LEVELS::LEVELONE:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (totalScore >= 35000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (totalScore >= 60000)
		{
			GUI::GetInstance().GetImage("Star3").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		break;
	}
	case LEVELS::LEVELTWO:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (totalScore >= 55000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (totalScore >= 69500)
		{
			GUI::GetInstance().GetImage("Star3").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		break;
	}
	case LEVELS::LEVELTHREE:
	{
		GUI::GetInstance().GetImage("Star1").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);

		if (totalScore >= 50000)
		{
			GUI::GetInstance().GetImage("Star2").setTexture(TextureLoader::LoadTexture("GUI/Star_Full.png"), true);
		}
		if (totalScore >= 70000)
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
	GUI::GetInstance().CreateButton("Continue", // Key
		{
			"Continue", // Text / label
			{ ScreenCentre.x,ScreenCentre.y + 60}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadNextLevel(); // On Press Lambda
			}
		});
	GUI::GetInstance().CreateButton("Retry", // Key
		{
			"Retry", // Text / label
			{ ScreenCentre.x,ScreenCentre.y + 130}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::ReloadCurrentLevel();  // On Press Lambda
			}
		});
}

void LevelCompleteMenu::CreateText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateText("Score", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 20}, // Position
			"Score: " + FloatToString(*LevelLoader::GetScore(),0) // Text / label
		});
}
