// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Bird.h 
// Description  : Bird Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "GameObject.h"

class Pig;
class Destructable;
class Bird : public GameObject
{
public:
	enum class TYPE
	{
		DEFAULT = 0,

		DASH,
		DIVEBOMB,
		EXPLOSIVE
	};

	/// <summary>
	/// Bird Constructor
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_startPos"></param>
	/// <param name="_birdType"></param>
	Bird(b2World& _world, sf::Vector2f _startPos, TYPE _birdType = TYPE::DEFAULT);
	/// <summary>
	/// Bird Destructor
	/// </summary>
	~Bird();

	/// <summary>
	/// Handles updating the bird
	/// </summary>
	virtual void Update() override;
	
	/// <summary>
	/// Activates the birds special ability
	/// </summary>
	/// <param name="_pigs"></param>
	/// <param name="_destructables"></param>
	virtual void SpecialAbility(std::vector<Pig*>& _pigs, std::vector<Destructable*>& _destructables);

	/// <summary>
	/// Creates the physics body and Launch the bird with the specified impulse
	/// </summary>
	/// <param name="_impulse"></param>
	void Launch(sf::Vector2f _impulse);

	/// <summary>
	/// Gives the player 10000 points.
	/// </summary>
	void AwardUnusedBirdScore();

	/// <summary>
	/// Sets the bird type and updates its sprite accordingly
	/// </summary>
	/// <param name="_birdType"></param>
	void SetBirdType(TYPE _birdType);

private:
	TYPE m_Type{ TYPE::DEFAULT };
	bool m_AbilityUsed{ false };

	/// <summary>
	/// Updates the sprite texture and body shape according too the bird type
	/// </summary>
	void SetTextureAndBodyBasedOnType();

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	sf::Vector2f GetLaunchVelocity(sf::Vector2f _launchVector);

	float GetScoreValue();
};

