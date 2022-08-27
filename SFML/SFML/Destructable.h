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
		WHEEL
	};
	enum class TYPE
	{
		UNASSIGNED = 0,

		WOOD,
		STONE,
		ICE
	};

	Destructable(b2World& _world, sf::Vector2f _startPos, SHAPE _shape = SHAPE::UNASSIGNED, TYPE _type = TYPE::UNASSIGNED);
	~Destructable();

	virtual void Start() override;
	virtual void Update() override;

	void TakeDamage(float _amount);
private:
	void InitBasedOnType();

	TYPE m_Type;
	SHAPE m_Shape;
	float m_DamageTimer = 0.0f;
	float m_DamageInterval = 0.3f;
	float m_CurrentHealth = 10.0f;
	float m_MaxHealth = 10.0f;
};

