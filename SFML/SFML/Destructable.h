// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Destructable.h 
// Description  : Destructable Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameObject.h"

class Destructable :
    public GameObject
{
public:
	enum class SHAPE
	{
		UNASSIGNED = 0,

		PLANK,
		SQUARE,
		TRIANGLE,
		WIDE,
		WHEEL,
		CORNER
	};
	enum class TYPE
	{
		UNASSIGNED = 0,

		WOOD,
		STONE,
		ICE,
		DIAMOND
	};
	enum class DAMAGELEVEL
	{
		UNASSIGNED = 0,

		FRESH,
		TIER1,
		TIER2,
		TIER3
	};

	/// <summary>
	/// Destrucable Constructor
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_startPos"></param>
	/// <param name="_shape"></param>
	/// <param name="_type"></param>
	Destructable(b2World& _world, sf::Vector2f _startPos, SHAPE _shape = SHAPE::UNASSIGNED, TYPE _type = TYPE::UNASSIGNED);
	/// <summary>
	/// Destructable Destructor
	/// </summary>
	~Destructable();

	/// <summary>
	/// Updates the destructable object
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
	void TakeDamage(float _amount, b2Vec2 _hitPos, sf::Color _pointColor = sf::Color::Red);

private:
	/// <summary>
	/// Initalize the destructable with texture, health e.t.c based on the type given on construction
	/// </summary>
	void InitBasedOnType();
	/// <summary>
	/// Sets the destructables damageLevel based on its currentHealth
	/// </summary>
	void UpdateDamageLevelFromHealth();

	/// <summary>
	/// Sets the current health to max health
	/// </summary>
	void SetHealthToMax();

	DAMAGELEVEL m_DamageLevel{ DAMAGELEVEL::FRESH };
	TYPE m_Type{TYPE::UNASSIGNED};
	SHAPE m_Shape{SHAPE::UNASSIGNED};
	float m_DamageTimer{};
	float m_DamageInterval{ 0.3f };
	float m_CurrentHealth{ 10.0f };
	float m_MaxHealth{ 10.0f };

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	float GetScoreValue();
};

