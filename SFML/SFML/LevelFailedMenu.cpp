#include "LevelFailedMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Math.h"
#include "LevelLoader.h"

LevelFailedMenu::LevelFailedMenu()
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

	GUI::GetInstance().CreateText("Score",
		{
			{ScreenCentre.x, ScreenCentre.y - 20},
			"Score: " + FloatToString(*LevelLoader::GetScore(),0)
		});

	GUI::GetInstance().CreateText("MissionFailed",
		{
			{ScreenCentre.x, ScreenCentre.y - 110},
			"Mission Failed!"
		});

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

void LevelFailedMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Retry",
		{
			"Retry",
			{ ScreenCentre.x,ScreenCentre.y + 60},
			{1,1},
			[]()
			{
				LevelLoader::ReloadCurrentLevel();
			}
		});

	GUI::GetInstance().CreateButton("Quit",
		{
			"Quit",
			{ ScreenCentre.x,ScreenCentre.y + 130},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::MAINMENU);
			}
		});

}
