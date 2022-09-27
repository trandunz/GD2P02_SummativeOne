// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Main.cpp 
// Description  : Main Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "AudioManager.h"
#include "TextureLoader.h"
#include "LevelLoader.h"
#include "Statics.h"
#include "GUI.h"

/// <summary>
/// Initalize the render window with the specified parameter
/// </summary>
/// <param name="_size"></param>
/// <param name="_title"></param>
/// <param name="_style"></param>
/// <param name="_settings"></param>
void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);

/// <summary>
/// Main Start Function
/// </summary>
void Start();
/// <summary>
/// Main Update Loop
/// </summary>
void Update();
/// <summary>
/// Main Event Polling
/// </summary>
void PollEvents();
/// <summary>
/// Main Render Function
/// </summary>
void Render();

/// <summary>
/// Cleanup everything and return 0 if no error
/// </summary>
/// <returns></returns>
int Cleanup();

int main()
{
	Start();
	Update();

	return Cleanup();
}

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings)
{
	Statics::RenderWindow.create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
}

void Start()
{
	// Init RenderWindow
	InitRenderWindow({ 1280, 720 }, "Angry Birds", sf::Style::Default, sf::ContextSettings());
	Statics::RenderWindow.setFramerateLimit(60);
	Statics::RenderWindow.setKeyRepeatEnabled(false);

	// Main Font
	Statics::TimesNewRoman.loadFromFile("Resources/Fonts/TNR.ttf");

	// Load Main Menu
	LevelLoader::LoadLevel(LEVELS::MAINMENU);
}

void Update()
{
	while (Statics::RenderWindow.isOpen())
	{
		Statics::CalculateDeltaTime();
		PollEvents();

		LevelLoader::Update();
		GUI::GetInstance().Update();
		
		Render();

		LevelLoader::ChangeLevelIfLoaded();
	}
}

void PollEvents()
{
	if (Statics::RenderWindow.pollEvent(Statics::EventHandle))
	{
		if (Statics::EventHandle.type == sf::Event::Closed)
			Statics::RenderWindow.close();
		//if (Statics::EventHandle.type == sf::Event::Resized)
		//	HandleResizing();

		LevelLoader::PollEvents();
		GUI::GetInstance().PollEvents();
	}
}

void Render()
{
	Statics::RenderWindow.clear();

	LevelLoader::Draw();

	Statics::RenderWindow.display();
}

int Cleanup()
{
	LevelLoader::CleanupLevel();
	GUI::GetInstance().CleanupElements();
	TextureLoader::CleanupTextures();
	AudioManager::Cleanup();

	return 0;
}
