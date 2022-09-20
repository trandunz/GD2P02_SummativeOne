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
	GUI::GetInstance().CreateImage("Splash",
		{
			&TextureLoader::LoadTexture("GUI/SplashScreen.png"),
			ScreenCentre,
			{0.7f, 0.7f}
		});
}

void MainMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("LevelSetOne",
		{
			"",
			{ScreenCentre.x - 250, ScreenCentre.y},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELONE);
			},
			&TextureLoader::LoadTexture("GUI/LevelSetOne.png")
		});
	GUI::GetInstance().CreateButton("LevelSetTwo",
		{
			"",
			{ScreenCentre.x, ScreenCentre.y},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELTWO);
			},
			&TextureLoader::LoadTexture("GUI/LevelSetOne.png")
		});
	GUI::GetInstance().CreateButton("LevelSetThree",
		{
			"",
			{ScreenCentre.x + 250, ScreenCentre.y},
			{1,1},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELTHREE);
			},
			&TextureLoader::LoadTexture("GUI/LevelSetOne.png")
		});
}
