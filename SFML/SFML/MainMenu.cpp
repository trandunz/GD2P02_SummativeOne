// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: MainMenu.cpp 
// Description  : MainMenu Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "MainMenu.h"
#include "AudioManager.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"

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
	GUI::GetInstance().CreateImage("Splash", // Key
		{
			&TextureLoader::LoadTexture("GUI/SplashScreen.png"), // Texture
			ScreenCentre, // Position
			{0.7f, 0.7f} // Scale
		});
}

void MainMenu::CreateButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("LevelSetOne", // Key
		{
			"", // String / Label
			{ScreenCentre.x - 250, ScreenCentre.y}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELONE); // On press Lambda
			},
			&TextureLoader::LoadTexture("GUI/LevelSetOne.png") // Texture
		});
	GUI::GetInstance().CreateButton("LevelSetTwo", // Key
		{
			"", // String / Label
			{ScreenCentre.x, ScreenCentre.y}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELTWO); // On press Lambda
			},
			&TextureLoader::LoadTexture("GUI/LevelSetTwo.png") // Texture
		});
	GUI::GetInstance().CreateButton("LevelSetThree", // Key
		{
			"", // String / Label
			{ScreenCentre.x + 250, ScreenCentre.y}, // Position
			{1,1}, // Scale
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::LEVELTHREE); // On press Lambda
			},
			&TextureLoader::LoadTexture("GUI/LevelSetThree.png") // Texture
		});
}
