// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Destructable.cpp 
// Description  : Destructable Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "Destructable.h"
#include "VFX.h"
#include "LevelLoader.h"

Destructable::Destructable(b2World& _world, sf::Vector2f _startPos, SHAPE _shape, TYPE _type)
	: GameObject(_world, _startPos)
{
	m_b2UserData.identifier = "Destructable";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);

	m_DamageLevel = DAMAGELEVEL::FRESH;
	m_Shape = _shape;
	m_Type = _type;
	InitBasedOnType();
	m_CurrentHealth = m_MaxHealth;
	SetBodyType(b2_dynamicBody);
	CreateBody();
}

Destructable::~Destructable()
{
	if (m_PhysicsBody)
	{
		m_PhysicsBody->DestroyJoints();
	}
}

void Destructable::Start()
{
}

void Destructable::Update()
{
	if (m_DamageTimer > 0.0f)
		m_DamageTimer -= Statics::DeltaTime;

	GameObject::Update();

	if (m_CurrentHealth <= 0.0f && m_Type != TYPE::DIAMOND)
		Destroy = true;
}

void Destructable::TakeDamage(float _amount)
{
	if (m_DamageTimer <= 0.0f && m_Type != TYPE::DIAMOND)
	{
		m_DamageTimer = m_DamageInterval;
		m_CurrentHealth -= _amount;

		if (m_CurrentHealth < 0.0f)
			m_CurrentHealth = 0.0f;

		UpdateDamageLevelFromHealth();
		InitBasedOnType();
	}
}

void Destructable::TakeDamage(float _amount, b2Vec2 _hitPos, sf::Color _pointColor)
{
	if (m_DamageTimer <= 0.0f && m_Type != TYPE::DIAMOND)
	{
		m_DamageTimer = m_DamageInterval;
		m_CurrentHealth -= _amount;

		if (m_CurrentHealth < 0.0f)
			m_CurrentHealth = 0.0f;

		UpdateDamageLevelFromHealth();
		InitBasedOnType();

		VFX::GetInstance().CreateAndPlayTextEffect(
			{
				FloatToString(GetScoreValue(), 0),
				{_hitPos.x * Statics::Scale, _hitPos.y * Statics::Scale},
				_pointColor,
				{1.5f,1.5f}
			}, 1.0f);

		*LevelLoader::GetScore() += GetScoreValue();
	}
}

float Destructable::GetScoreValue()
{
	return 500.0f;
}

void Destructable::InitBasedOnType()
{
	std::string subFolder = "";
	switch (m_Type)
	{
	case TYPE::WOOD:
	{
		m_MaxHealth = 10.0f;
		m_Mass = 1.0f;
		subFolder = "Wood/";
		break;
	}
	case TYPE::STONE:
	{
		m_MaxHealth = 20.0f;
		m_Mass = 2.0f;
		subFolder = "Stone/";
		break;
	}
	case TYPE::ICE:
	{
		m_MaxHealth = 5.0f;
		m_Mass = 1.0f;
		subFolder = "Ice/";
		break;
	}
	case TYPE::DIAMOND:
	{
		m_MaxHealth = 5.0f;
		m_Mass = 2.0f;
		subFolder = "Diamond/";
		break;
	}
	default:
		break;
	}

	std::string shape = "";
	switch (m_Shape)
	{
	case SHAPE::PLANK:
	{
		shape = "Plank (";
		break;
	}
	case SHAPE::SQUARE:
	{
		shape = "Square (";
		break;
	}
	case SHAPE::TRIANGLE:
	{
		m_BodyShape = BODYSHAPE::TRIANGLE;
		shape = "Triangle (";
		break;
	}
	case SHAPE::CORNER:
	{
		m_BodyShape = BODYSHAPE::CORNER;
		shape = "Corner (";
		break;
	}
	case SHAPE::WIDE:
	{
		shape = "WideBlock (";
		break;
	}
	case SHAPE::WHEEL:
	{
		m_BodyShape = BODYSHAPE::CIRCLE;
		shape = "BigWheel (";
		break;
	}
	default:
		break;
	}

	switch (m_DamageLevel)
	{
	case DAMAGELEVEL::FRESH:
	{
		SetTexture(subFolder + shape + "1).png");
		break;
	}
	case DAMAGELEVEL::TIER1:
	{
		SetTexture(subFolder + shape + "2).png");
		break;
	}
	case DAMAGELEVEL::TIER2:
	{
		SetTexture(subFolder + shape + "3).png");
		break;
	}
	case DAMAGELEVEL::TIER3:
	{
		SetTexture(subFolder + shape + "4).png");
		break;
	}
	default:
		break;
	}
}

void Destructable::UpdateDamageLevelFromHealth()
{
	float damageIncrement = m_MaxHealth / 4.0f;
	if (m_CurrentHealth <= damageIncrement)
	{
		m_DamageLevel = DAMAGELEVEL::TIER3;
	}
	else if (m_CurrentHealth <= damageIncrement * 2)
	{
		m_DamageLevel = DAMAGELEVEL::TIER2;
	}
	else if (m_CurrentHealth <= damageIncrement * 3)
	{
		m_DamageLevel = DAMAGELEVEL::TIER1;
	}
	else
	{
		m_DamageLevel = DAMAGELEVEL::FRESH;
	}
}
