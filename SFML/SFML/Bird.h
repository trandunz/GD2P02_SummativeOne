#pragma once
#include "GameObject.h"
class Bird : public GameObject
{
public:
	Bird(b2World& _world, sf::Vector2f _startPos);
	~Bird();

	virtual void Start() override;
	virtual void Update() override;

	sf::Vector2f GetLaunchVelocity(sf::Vector2f _launchVector);
	void Launch(sf::Vector2f _impulse);

	float GetScoreValue();
	void AwardUnusedBirdScore();
};

