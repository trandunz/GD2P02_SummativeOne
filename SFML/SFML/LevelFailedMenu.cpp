// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelFailedMenu.cpp 
// Description  : LevelFailedMenu Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "LevelFailedMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Math.h"
#include "LevelLoader.h"

LevelFailedMenu::LevelFailedMenu()
{
	CreateMenuBackground();
	CreateText();
	CreateButtons();
}

LevelFailedMenu::~LevelFailedMenu()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("Score");
	GUI::GetInstance().CleanupTextElement("MissionFailed");
	GUI::GetInstance().CleanupButtonElement("Quit");
	GUI::GetInstance().CleanupButtonElement("Retry");
}

void LevelFailedMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateImage("DullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Set Texture
			ScreenCentre // Position
		});

	GUI::GetInstance().CreateImage("Background", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Set Texture
			ScreenCentre, // Position
			{1.5f,1.5f} // Scale
		});
}

void LevelFailedMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Retry", // Key
		{
			"Retry", // Label / string
			{ ScreenCentre.x,ScreenCentre.y + 60}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::ReloadCurrentLevel(); // On Press Lambda
			}
		});

	GUI::GetInstance().CreateButton("Quit", // Key
		{
			"Quit", // Label / string
			{ ScreenCentre.x,ScreenCentre.y + 130}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::MAINMENU); // On Press Lambda
			}
		});

}

void LevelFailedMenu::CreateText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("Score", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 20}, // Position
			"Score: " + FloatToString(*LevelLoader::GetScore(),0) // Label / string
		});

	GUI::GetInstance().CreateText("MissionFailed", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 110}, // Position
			"Mission Failed!" // Label / string
		});
}
