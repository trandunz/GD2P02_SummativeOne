#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct UserData
{
	std::string identifier;
	uintptr_t data;
};

class Statics
{
public:
	static sf::Event EventHandler;
	static sf::RenderWindow RenderWindow;
	
	static void CalculateDeltaTime();
	static sf::Clock Time;
	static float DeltaTime;
	static float UnscaledDeltaTime;
	static float TimeScale;

	static float Scale;

	static sf::Font TimesNewRoman;
private:
	static float LastTime;
};

