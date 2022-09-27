// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Pig.h 
// Description  : Pig Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameObject.h"

class Pig : public GameObject
{
public:
	/// <summary>
	/// Pig Constructor
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_startPos"></param>
	/// <param name="_maxHP"></param>
	Pig(b2World& _world, sf::Vector2f _startPos, float _maxHP = 10.0f);
	/// <summary>
	/// Pig Destructor
	/// </summary>
	~Pig();

	/// <summary>
	/// Handles updating the pig
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// Handles taking the specified amount of damage
	/// </summary>
	/// <param name="_amount"></param>
	void TakeDamage(float _amount);
	/// <summary>
	/// Handles taking damage and also spawns a points indicator at the hitPos
	/// </summary>
	/// <param name="_amount"></param>
	/// <param name="_hitPos"></param>
	/// <param name="_pointColor"></param>
	void TakeDamage(float _amount, b2Vec2 _hitPos, sf::Color _pointColor = sf::Color::Green);

private:
	float m_DamageTimer = 0.0f;
	float m_DamageInterval = 0.3f;
	float m_CurrentHealth = 10.0f;
	float m_MaxHealth = 10.0f;

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	float GetScoreValue();
};

