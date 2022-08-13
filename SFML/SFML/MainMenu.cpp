#include "MainMenu.h"

MainMenu::MainMenu()
{
	World = new b2World({ 0,10.0f });

	m_Music.openFromFile("Resources/Sounds/ThemeSong.WAV");
	m_Music.play();
	m_Music.setLoop(true);

	CreateMeshes();
	CreateButtons();
}

MainMenu::~MainMenu()
{
	for (auto& sprite : m_Meshes)
	{
		if (sprite)
			delete sprite;
		sprite = nullptr;
	}
	m_Meshes.clear();

	for (auto& button : m_Buttons)
	{
		if (button)
			delete button;
		button = nullptr;
	}
	m_Buttons.clear();

	if (World)
		delete World;
	World = nullptr;
}

void MainMenu::PollEvents(sf::Event& _event)
{
	if (_event.type == sf::Event::MouseButtonPressed)
	{
		for (auto& button : m_Buttons)
		{
			button->CallOnPress();
		}
	}
}

void MainMenu::Update()
{

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& sprite : m_Meshes)
	{
		target.draw(*sprite);
	}
	for (auto& button : m_Buttons)
	{
		target.draw(*button);
	}
}

void MainMenu::CreateMeshes()
{
	sf::Vector2f ScreenCentre = Helper::RenderWindow.getView().getCenter();
	m_Meshes.emplace_back(new Mesh("Title.png", { ScreenCentre.x, 100 }));
}

void MainMenu::CreateButtons()
{
	m_Buttons.emplace_back(new Button("Play", (sf::Vector2f)Helper::RenderWindow.getSize() / 2.0f,
		[]()
		{
			LevelManager::LoadLevel(new Level);
		},
		{ 2.0f,2.0f }));
}
