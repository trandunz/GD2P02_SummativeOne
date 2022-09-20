#include "LevelCompleteMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
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
			&TextureLoader::LoadTexture("GUI/Star_Full.png"),
			{ScreenCentre.x - 75, ScreenCentre.y - 100},
			{1.2f,1.2f},
			45.0f
		});

	GUI::GetInstance().CreateImage("Star2",
		{
			&TextureLoader::LoadTexture("GUI/Star_Full.png"),
			{ScreenCentre.x, ScreenCentre.y - 110},
			{1.5f,1.5f}
		});

	GUI::GetInstance().CreateImage("Star3",
		{
			&TextureLoader::LoadTexture("GUI/Star_Full.png"),
			{ScreenCentre.x + 75, ScreenCentre.y - 100},
			{1.2f,1.2f},
			-45.0f
		});

	CreateButtons();
}

LevelCompleteMenu::~LevelCompleteMenu()
{
	m_Buttons.clear();
	m_Buttons.resize(0);

	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupButtonElement("Continue");
	GUI::GetInstance().CleanupButtonElement("Retry");
	GUI::GetInstance().CleanupButtonElement("Quit");
}

void LevelCompleteMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& button : m_Buttons)
		target.draw(button);
}

void LevelCompleteMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Continue",
		{
			"Continue",
			{ ScreenCentre.x,ScreenCentre.y + 10},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::MAINMENU);
			}
		});
	GUI::GetInstance().CreateButton("Retry",
		{
			"Retry",
			{ ScreenCentre.x,ScreenCentre.y + 110},
			{1,1},
			[]()
			{
				LevelLoader::ReloadCurrentLevel();
			}
		});
}
