// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PauseMenu.cpp 
// Description  : PauseMenu Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "PauseMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"

PauseMenu::PauseMenu()
{
	CreateMenuBackground();
	CreateText();
	CreateButtons();
}

PauseMenu::~PauseMenu()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("PauseMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Retry");
	GUI::GetInstance().CleanupButtonElement("Quit");
}

void PauseMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Retry", // Key
		{
			"Retry", // Label / String
			{ ScreenCentre.x,ScreenCentre.y}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::ReloadCurrentLevel();	// On Press Lambda
				Statics::TogglePaused();
			}
		});
	GUI::GetInstance().CreateButton("Quit", // Key
		{
			"Quit", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 80}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::MAINMENU); // On Press Lambda
				Statics::TogglePaused();
			}
		});
}

void PauseMenu::CreateText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("PauseMenuTitle", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 80}, // Position
			"Paused" // Label / String
		});
}

void PauseMenu::CreateMenuBackground()
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
			ScreenCentre // Position
		});
}
