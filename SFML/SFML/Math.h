#pragma once
#include "SFML/Graphics.hpp"

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


