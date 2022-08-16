#include "AudioManager.h"
#include "TextureLoader.h"
#include "MainMenu.h"
#include "Statics.h"

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);

void Start();
void Update();
void PollEvents();
void Render();

int Cleanup();

void HandleResizing();


int main()
{
	Start();
	Update();
	Render();

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
	LevelLoader::LoadLevel(new MainMenu());
}

void Update()
{
	while (Statics::RenderWindow.isOpen())
	{
		Statics::CalculateDeltaTime();
		PollEvents();

		LevelLoader::Update();
		
		Render();
	}
}

void PollEvents()
{
	if (Statics::RenderWindow.pollEvent(Statics::EventHandler))
	{
		if ((Statics::EventHandler.type == sf::Event::KeyPressed
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			|| Statics::EventHandler.type == sf::Event::Closed)
		{
			Statics::RenderWindow.close();
		}
		if (Statics::EventHandler.type == sf::Event::Resized)
			HandleResizing();

		LevelLoader::PollEvents();
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
	TextureLoader::CleanupTextures();
	AudioManager::Cleanup();

	return 0;
}

void HandleResizing()
{
	sf::Vector2f size = (sf::Vector2f)Statics::RenderWindow.getSize();

	if (size.x < 426)
		size.x = 426;
	if (size.y < 240)
		size.y = 240;

	Statics::RenderWindow.setSize((sf::Vector2u)size);
}
