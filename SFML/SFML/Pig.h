#pragma once
#include "GameObject.h"

class Pig : public GameObject
{
public:
	Pig(b2World& _world, sf::Vector2f _startPos, float _maxHP = 10.0f);
	~Pig();

	virtual void Start() override;
	virtual void Update() override;

	void TakeDamage(float _amount);

	float GetScoreValue();
private:
	float m_DamageTimer = 0.0f;
	float m_DamageInterval = 0.3f;
	float m_CurrentHealth = 10.0f;
	float m_MaxHealth = 10.0f;
};

