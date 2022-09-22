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

	Bird(b2World& _world, sf::Vector2f _startPos, TYPE _birdType = TYPE::DEFAULT);

	~Bird();

	virtual void Start() override;
	virtual void Update() override;
	
	virtual void SpecialAbility(std::vector<Pig*>& _pigs, std::vector<Destructable*>& _destructables);

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

