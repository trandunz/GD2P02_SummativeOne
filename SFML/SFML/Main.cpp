#include "LevelManager.h"

sf::Event EventHandle;
sf::Clock MainClock;

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);

void Start();
void Update();
void PollEvents();
void Render();

int Cleanup();

void CalculateDeltaTime();


int main()
{
	InitRenderWindow({ 1200, 600 }, "Title", sf::Style::Default, sf::ContextSettings());

	Start();
	Update();
	Render();

	return Cleanup();
}

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings)
{
	Helper::RenderWindow.create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
}

void Start()
{
	Helper::RenderWindow.setVerticalSyncEnabled(true);

	LevelManager::LoadLevel(new Level());
}

void Update()
{
	while (Helper::RenderWindow.isOpen())
	{
		CalculateDeltaTime();
		PollEvents();

		LevelManager::CurrentLevel->Update();
		
		Render();
	}
}

void PollEvents()
{
	if (Helper::RenderWindow.pollEvent(EventHandle))
	{
		if (EventHandle.type == sf::Event::Closed)
		{
			Helper::RenderWindow.close();
		}

		LevelManager::CurrentLevel->PollEvents(EventHandle);
	}
}

void Render()
{
	Helper::RenderWindow.clear();

	Helper::RenderWindow.draw(*LevelManager::CurrentLevel);

	Helper::RenderWindow.display();
}

int Cleanup()
{
	LevelManager::CleanupLevel();

	return 0;
}

void CalculateDeltaTime()
{
	sf::Int32 currentTime = MainClock.getElapsedTime().asMilliseconds();
	Helper::DeltaTime = currentTime - Helper::LastTime;
	Helper::LastTime = currentTime;
}
