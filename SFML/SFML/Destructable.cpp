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

	if (m_Mesh)
	{
		switch (m_Shape)
		{
		case SHAPE::PLANK:
		{
			SetTexture(subFolder + "Plank (1).png");
			break;
		}
		case SHAPE::SQUARE:
		{
			SetTexture(subFolder + "Square (1).png");
			break;
		}
		case SHAPE::TRIANGLE:
		{
			SetTexture(subFolder + "Triangle (1).png");
			break;
		}
		case SHAPE::WIDE:
		{
			SetTexture(subFolder + "WideBlock (1).png");
			break;
		}
		case SHAPE::WHEEL:
		{
			SetTexture(subFolder + "BigWheel (1).png");
			break;
		}
		default:
			break;
		}
	}
}
