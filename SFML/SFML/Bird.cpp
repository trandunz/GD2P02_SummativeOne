#include "Bird.h"

struct UserData
{
	std::string identifier;
	uintptr_t data;
};

Bird::Bird(b2World& _world, sf::Vector2f _startPos)
	: GameObject(_world, _startPos)
{
	m_b2UserData->identifier = "Bird";
	m_b2UserData->data = reinterpret_cast<uintptr_t>(this);
}

Bird::~Bird()
{
}

void Bird::Start()
{
}

void Bird::Update()
{
	if (m_PhysicsBody != nullptr)
	{
		m_PhysicsBody->Update();
		m_Mesh->SetPosition(m_PhysicsBody->GetPosition());
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