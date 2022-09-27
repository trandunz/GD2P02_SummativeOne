// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Math.h 
// Description  : Math Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_math.h>
#include <sstream>
#include <iomanip>

/// <summary>
/// Returns the magnitude of the vector
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
inline float Mag(sf::Vector2f _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
/// <summary>
/// Returns the magnitude of the vector
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
inline float Mag(b2Vec2 _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
/// <summary>
/// Returns the normalized version of the vector
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
inline sf::Vector2f Normalize(sf::Vector2f _vector)
{
	float mag = Mag(_vector);
	if (mag <= 0)
	{
		return {};
	}
	return _vector / Mag(_vector);
}
/// <summary>
/// Sets the origin of the sprite too its centre
/// </summary>
/// <param name="_sprite"></param>
inline void SetOriginCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin({ (_sprite.getLocalBounds().width) / 2.0f, (_sprite.getLocalBounds().height) / 2.0f});
}
/// <summary>
/// Sets the origin of the text too its centre
/// </summary>
/// <param name="_text"></param>
inline void SetOriginCentre(sf::Text& _text)
{
	_text.setOrigin({ (_text.getLocalBounds().width) / 2.0f, (_text.getLocalBounds().height) / 1.25f});
}
/// <summary>
/// Converts and rounds the float too a string
/// </summary>
/// <param name="_float"></param>
/// <param name="_precision"></param>
/// <returns></returns>
inline std::string FloatToString(float _float, int _precision = 2)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(_precision) << _float;
	return stream.str();
}


