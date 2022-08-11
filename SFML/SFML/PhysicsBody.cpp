#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(b2World& _world, sf::Vector2f _size, sf::Vector2f _startPos)
{
	m_World = &_world;
	SetupBody(_startPos, _size, 0.6f);
}

PhysicsBody::~PhysicsBody()
{
	m_World->DestroyBody(m_Body);
	m_Body = nullptr;
	m_World = nullptr;
}

void PhysicsBody::ApplyImpulse(sf::Vector2f _impulse)
{
	m_Body->ApplyLinearImpulseToCenter({ _impulse.x, _impulse.y}, true);
}

void PhysicsBody::SetBodyType(b2BodyType _bodyType)
{
	m_Body->GetFixtureList()[0].GetBody()->SetType(_bodyType);
}

void PhysicsBody::SetPosition(sf::Vector2f _position)
{
	m_Position = { _position.x / Helper::Scale, _position.y / Helper::Scale, };
	if (m_Body)
		m_Body->SetTransform({ _position.x / Helper::Scale, _position.y / Helper::Scale, }, 0.0f);
}

sf::Vector2f PhysicsBody::GetPosition()
{
	if (m_Body)
	{
		return {m_Body->GetPosition().x * Helper::Scale ,m_Body->GetPosition().y * Helper::Scale };
	}
	else
	{
		return sf::Vector2f();
	}
}

void PhysicsBody::SetSize(sf::Vector2f _size)
{
	if (m_Body)
		m_World->DestroyBody(m_Body);
	m_Body = nullptr;

	SetupBody(m_Position, _size);
}

void PhysicsBody::SetupBody(sf::Vector2f _position, sf::Vector2f _size, float _restitution, float _density)
{
	b2BodyDef bodyDef;
	bodyDef.allowSleep = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(_position.x / Helper::Scale, _position.y / Helper::Scale);
	m_Body = m_World->CreateBody(&bodyDef);

	m_Position = _position;

	b2PolygonShape shape;
	shape.SetAsBox((_size.x / 2) / Helper::Scale, (_size.y / 2) / Helper::Scale);

	b2FixtureDef fixtureDef;
	fixtureDef.density = _density;
	fixtureDef.shape = &shape;
	fixtureDef.restitution = _restitution;
	m_Body->CreateFixture(&fixtureDef);
}
