#include "Destructable.h"

Destructable::Destructable(b2World& _world, sf::Vector2f _startPos, SHAPE _shape, TYPE _type)
	: GameObject(_world, _startPos)
{
	m_b2UserData.identifier = "Destructable";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);

	m_Shape = _shape;
	m_Type = _type;
	InitBasedOnType();
	m_CurrentHealth = m_MaxHealth;
	SetBodyType(b2_dynamicBody);
	CreateBody();
}

Destructable::~Destructable()
{
}

void Destructable::Start()
{
}

void Destructable::Update()
{
	if (m_DamageTimer > 0.0f)
		m_DamageTimer -= Statics::DeltaTime;

	GameObject::Update();

	if (m_CurrentHealth <= 0.0f)
		Destroy = true;
}

void Destructable::TakeDamage(float _amount)
{
	if (m_DamageTimer <= 0.0f)
	{
		m_DamageTimer = m_DamageInterval;
		m_CurrentHealth -= _amount;

		if (m_CurrentHealth < 0.0f)
			m_CurrentHealth = 0.0f;

		UpdateDamageLevelFromHealth();
		InitBasedOnType();
	}
}

void Destructable::InitBasedOnType()
{
	std::string subFolder = "";
	switch (m_Type)
	{
	case TYPE::WOOD:
	{
		m_MaxHealth = 10.0f;
		subFolder = "Wood/";
		break;
	}
	case TYPE::STONE:
	{
		m_MaxHealth = 20.0f;
		subFolder = "Stone/";
		break;
	}
	case TYPE::ICE:
	{
		m_MaxHealth = 5.0f;
		subFolder = "Ice/";
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
		shape = "Triangle (";
		break;
	}
	case SHAPE::WIDE:
	{
		shape = "WideBlock (";
		break;
	}
	case SHAPE::WHEEL:
	{
		shape = "BigWheel (";
		break;
	}
	default:
		break;
	}

	if (m_Mesh)
	{
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
