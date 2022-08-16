#include "MainMenu.h"
#include "LevelOne.h"
#include"AudioManager.h"

MainMenu::MainMenu()
{
	AudioManager::PlayMusic("ThemeSong.WAV");

	CreateMeshes();
	CreateButtons();
}

MainMenu::~MainMenu()
{
	m_Meshes.clear();
	m_Buttons.clear();
}

void MainMenu::PollEvents()
{
	if (Statics::EventHandler.type == sf::Event::MouseButtonPressed)
	{
		for (auto& button : m_Buttons)
		{
			button.CallOnPress();
		}
	}
}

void MainMenu::Update()
{

}

void MainMenu::Draw()
{
	for (auto& sprite : m_Meshes)
	{
		Statics::RenderWindow.draw(sprite);
	}
	for (auto& button : m_Buttons)
	{
		Statics::RenderWindow.draw(button);
	}
}

void MainMenu::CreateMeshes()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	m_Meshes.emplace_back(Mesh("Title.png", { ScreenCentre.x, 100 }));
}

void MainMenu::CreateButtons()
{
	m_Buttons.emplace_back(Button({ "Level One", { 640,300},
		[]()
		{
			LevelLoader::LoadLevel(new LevelOne);
		},
		{ 2.0f,2.0f } }));
	m_Buttons.emplace_back(Button({"Level Two", { 640,450 },
		[]()
		{
			LevelLoader::LoadLevel(new LevelOne);
		},
		{ 2.0f,2.0f }}));
	m_Buttons.emplace_back(Button({ "Level Three", { 640,600 },
		[]()
		{
			LevelLoader::LoadLevel(new LevelOne);
		},
		{ 2.0f,2.0f } }));
}
