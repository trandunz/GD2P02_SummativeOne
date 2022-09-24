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
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("DullBackground",
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"),
			ScreenCentre
		});
	
	GUI::GetInstance().CreateImage("Background",
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"),
			ScreenCentre
		});

	GUI::GetInstance().CreateText("PauseMenuTitle",
		{
			{ScreenCentre.x, ScreenCentre.y - 80},
			"Paused"
		});

	CreateButtons();
}

PauseMenu::~PauseMenu()
{
	m_Buttons.clear();
	m_Buttons.resize(0);

	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("PauseMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Retry");
	GUI::GetInstance().CleanupButtonElement("Quit");
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& button : m_Buttons)
		target.draw(button);
}

void PauseMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Retry",
		{
			"Retry",
			{ ScreenCentre.x,ScreenCentre.y},
			{1,1},
			[]()
			{
				LevelLoader::ReloadCurrentLevel();
				Statics::TogglePaused();
			}
		});
	GUI::GetInstance().CreateButton("Quit",
		{
			"Quit",
			{ ScreenCentre.x,ScreenCentre.y + 80},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::MAINMENU);
				Statics::TogglePaused();
			}
		});
}
