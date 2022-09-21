#include "Bird.h"
#include "VFX.h"
#include "LevelLoader.h"

Bird::Bird(b2World& _world, sf::Vector2f _startPos, TYPE _birdType)
	: GameObject(_world, _startPos)
{
	m_b2UserData.identifier = "Bird";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);
	m_Type = _birdType;

	SetTextureBasedOnType();
	SetScale({ 0.25f,0.25f });
	SetBodyType(b2_dynamicBody);
}

Bird::~Bird()
{
}

void Bird::Start()
{
}

void Bird::Update()
{
	GameObject::Update();
	if (m_PhysicsBody)
	{
		if (Mag(m_PhysicsBody->GetVelocity()) <= 10.0f)
		{
			Destroy = true;
		}
	}
	if (GetPosition().x < -m_Mesh->GetGlobalBounds().width
		|| GetPosition().x > Statics::RenderWindow.getSize().x + m_Mesh->GetGlobalBounds().width)
	{
		Destroy = true;
	}
}

void Bird::SpecialAbility()
{
	if (m_AbilityUsed == false)
	{
		if (m_PhysicsBody)
		{
			m_AbilityUsed = true;
			switch (m_Type)
			{
			case TYPE::DIVEBOMB:
			{
				m_PhysicsBody->ApplyImpulse(-m_PhysicsBody->GetVelocity() / Statics::Scale);
				m_PhysicsBody->ApplyImpulse({ 0, 50.0f });
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

sf::Vector2f Bird::GetLaunchVelocity(sf::Vector2f _launchVector)
{
	return _launchVector;
}

void Bird::Launch(sf::Vector2f _impulse)
{
	CreateBody();
	m_PhysicsBody->ApplyImpulse(_impulse);
}

float Bird::GetScoreValue()
{
	return 10000.0f;
}

void Bird::AwardUnusedBirdScore()
{
	VFX::GetInstance().CreateAndPlayTextEffect(
		{
			FloatToString(GetScoreValue(), 0),
			GetPosition(),
			sf::Color::Green,
			{1.5f,1.5f}
		}, 1.0f);

	*LevelLoader::GetScore() += GetScoreValue();
}

void Bird::SetBirdType(TYPE _birdType)
{
	m_Type = _birdType;

	SetTextureBasedOnType();
}

void Bird::SetTextureBasedOnType()
{
	switch (m_Type)
	{
	case TYPE::DIVEBOMB:
	{
		m_Mesh->SetTexture("Bird_DiveBomb.png");
		m_BodyShape = BODYSHAPE::TRIANGLE;
		break;
	}
	default:
	{
		m_Mesh->SetTexture("Bird_Default.png");
		m_BodyShape = BODYSHAPE::CIRCLE;
		break;
	}
	}
}
