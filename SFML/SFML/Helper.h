#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class Helper
{
public:
	static void SetOriginCentre(sf::Sprite& _sprite);
	static void SetOriginCentre(sf::Text& _text);
	static sf::RenderWindow RenderWindow;
	static sf::Font TimesNewRoman;
	static sf::Int32 DeltaTime;
	static sf::Int32 LastTime;
	static float Scale;
};

