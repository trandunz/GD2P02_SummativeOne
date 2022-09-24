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
	Pig(b2World& _world, sf::Vector2f _startPos, float _maxHP = 10.0f);
	/// <summary>
	/// Pig Destructor
	/// </summary>
	~Pig();

	virtual void Start() override;
	virtual void Update() override;

	void TakeDamage(float _amount);
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

