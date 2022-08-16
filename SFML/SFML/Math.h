#pragma once
#include <SFML/Graphics.hpp>

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

inline void SetOriginCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin({ _sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2 });
}

inline void SetOriginCentre(sf::Text& _text)
{
	_text.setOrigin({ _text.getLocalBounds().width / 2, _text.getLocalBounds().height / 1.25f });
}


