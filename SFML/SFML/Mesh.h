// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Mesh.h 
// Description  : Mesh Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Statics.h"
#include "Math.h"

class Mesh : public sf::Drawable
{
public:
	/// <summary>
	/// Mesh Constructor
	/// </summary>
	/// <param name="_spriteName"></param>
	/// <param name="_position"></param>
	/// <param name="_scale"></param>
	Mesh(std::string _spriteName, sf::Vector2f _position = { 0,0 }, sf::Vector2f _scale = { 1,1 });
	/// <summary>
	/// Mesh Destructor
	/// </summary>
	~Mesh();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite m_Sprite{};

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	void SetTexture(std::string _spriteName);

	void SetScale(sf::Vector2f _scale);

	inline sf::Vector2f GetPosition() { return m_Sprite.getPosition(); }
	void SetPosition(sf::Vector2f _position);

	float GetRotation();
	void SetRotation(float _radians);

	sf::FloatRect GetLocalBounds();

	sf::FloatRect GetGlobalBounds();

	sf::Vector2f GetSize();

};

