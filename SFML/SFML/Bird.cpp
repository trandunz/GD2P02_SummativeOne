#include "Bird.h"

Bird::Bird(b2World& _world, sf::Vector2f _startPos)
	: GameObject(_world, _startPos)
{
	m_b2UserData.identifier = "Bird";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);
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
