#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <functional>

#define PI 3.141592654

struct UserData
{
	std::string identifier;
	uintptr_t data;
};

class Statics
{
public:
	static sf::Event EventHandle;
	static sf::RenderWindow RenderWindow;
	
	static void CalculateDeltaTime();
	static sf::Clock Time;
	static float DeltaTime;
	static float UnscaledDeltaTime;
	static float TimeScale;
	static bool IsPaused;
	static void TogglePaused();

	static float Scale;

	static sf::Font TimesNewRoman;
private:
	static float LastTime;
};

