#include "Bird.h"
#include "VFX.h"
#include "LevelLoader.h"
#include "Pig.h"
#include "Destructable.h"

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

void Bird::SpecialAbility(std::vector<Pig*>& _pigs, std::vector<Destructable*>& _destructables)
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
				m_PhysicsBody->ApplyImpulse({0.0f, 25.0f });
				break;
			}
			case TYPE::DASH:
			{
				m_PhysicsBody->ApplyImpulse({ 18.0f, 0.0f });
				break;
			}
			case TYPE::EXPLOSIVE:
			{
				for (auto& pig : _pigs)
				{
					sf::Vector2f directionToPig = pig->GetPosition() - m_PhysicsBody->GetPosition();
					if (Mag(directionToPig) <= 200.0f)
					{
						pig->GetPhysicsBody()->ApplyImpulse(Normalize(directionToPig) * 10.0f);
					}
				}
				for (auto& destructable : _destructables)
				{
					sf::Vector2f directionToDestructable = destructable->GetPosition() - m_PhysicsBody->GetPosition();
					if (Mag(directionToDestructable) <= 200.0f)
					{
						destructable->GetPhysicsBody()->ApplyImpulse(Normalize(directionToDestructable) * 10.0f);
					}
				}
				Destroy = true;
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
		m_BodyShape = BODYSHAPE::CIRCLE;
		break;
	}
	case TYPE::DASH:
	{
		m_Mesh->SetTexture("Bird_Dash.png");
		m_BodyShape = BODYSHAPE::TRIANGLE;
		break;
	}
	case TYPE::EXPLOSIVE:
	{
		m_Mesh->SetTexture("Bird_Explosive.png");
		m_BodyShape = BODYSHAPE::CIRCLE;
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
