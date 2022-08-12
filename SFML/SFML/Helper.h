#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

inline float Mag(sf::Vector2f _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}

inline sf::Vector2f Normalize(sf::Vector2f _vector)
{
	float mag = Mag(_vector);
	if (mag <= 0)
	{
		return {};
	}
	return _vector / Mag(_vector);
}

class Helper
{
public:
	static void SetOriginCentre(sf::Sprite& _sprite);
	static void SetOriginCentre(sf::Text& _text);
	static sf::RenderWindow RenderWindow;
	static sf::Int32 DeltaTime;
	static sf::Int32 LastTime;
	static float Scale;
};

