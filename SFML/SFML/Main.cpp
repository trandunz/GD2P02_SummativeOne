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
void HandleResizing();


int main()
{
	InitRenderWindow({ 1280, 720 }, "Angry Birds", sf::Style::Default, sf::ContextSettings());

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
	Helper::RenderWindow.setFramerateLimit(60);

	LevelManager::LoadLevel(new MainMenu());
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
		if ((EventHandle.type == sf::Event::KeyPressed
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			|| EventHandle.type == sf::Event::Closed)
		{
			Helper::RenderWindow.close();
		}
		if (EventHandle.type == sf::Event::Resized)
			HandleResizing();

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

void HandleResizing()
{
	sf::Vector2f size = (sf::Vector2f)Helper::RenderWindow.getSize();

	if (size.x < 426)
		size.x = 426;
	if (size.y < 240)
		size.y = 240;

	Helper::RenderWindow.setSize((sf::Vector2u)size);
}
