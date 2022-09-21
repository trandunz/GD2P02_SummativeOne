#pragma once
#include "GameObject.h"

class Bird : public GameObject
{
public:
	enum class TYPE
	{
		DEFAULT = 0,

		DIVEBOMB
	};

	Bird(b2World& _world, sf::Vector2f _startPos, TYPE _birdType = TYPE::DEFAULT);

	~Bird();

	virtual void Start() override;
	virtual void Update() override;
	
	virtual void SpecialAbility();

	sf::Vector2f GetLaunchVelocity(sf::Vector2f _launchVector);
	void Launch(sf::Vector2f _impulse);

	float GetScoreValue();
	void AwardUnusedBirdScore();

	void SetBirdType(TYPE _birdType);

private:
	TYPE m_Type{ TYPE::DEFAULT };
	bool m_AbilityUsed{ false };

	void SetTextureBasedOnType();
};

