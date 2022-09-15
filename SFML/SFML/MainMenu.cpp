#include "MainMenu.h"
#include "AudioManager.h"
#include "GUI.h"
#include "TextureLoader.h"

MainMenu::MainMenu()
{
	AudioManager::PlayMusic("ThemeSong.WAV");

	CreateMeshes();
	CreateButtons();
}

MainMenu::~MainMenu()
{
	GUI::GetInstance().CleanupElements();
}

void MainMenu::PollEvents()
{
	if (Statics::EventHandle.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Statics::RenderWindow.close();
		}
	}
}

void MainMenu::Update()
{
}
 
void MainMenu::Draw()
{
	Statics::RenderWindow.draw(GUI::GetInstance());
}

void MainMenu::CreateMeshes()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateImage("Title",
		{
			&TextureLoader::LoadTexture("Title.png"),
			{ ScreenCentre.x, 100 }
		});
}

void MainMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("LevelOne",
		{
			"Level One",
			{ ScreenCentre.x,300},
			{2,2},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELONE);
			}
		});
	GUI::GetInstance().CreateButton("LevelTwo",
		{
			"Level Two",
			{ ScreenCentre.x,450},
			{2,2},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELONE);
			}
		});
	GUI::GetInstance().CreateButton("LevelThree",
		{
			"Level Three",
			{ ScreenCentre.x,600},
			{ 2,2 },
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELONE);
			}
		});
}
