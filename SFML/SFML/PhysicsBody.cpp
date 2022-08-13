#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape, b2BodyType _bodyType, float _restitution, float _density)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	if (_shape == nullptr)
		m_Shape = new b2PolygonShape();
	else
		m_Shape = _shape;
	SetupBody();
}

PhysicsBody::~PhysicsBody()
{
	DestroyBody();
	m_World = nullptr;

	if (m_Shape)
		delete m_Shape;
	m_Shape = nullptr;
}

void PhysicsBody::Update()
{
	m_Position =  { Helper::Scale * m_Body->GetPosition().x, Helper::Scale * m_Body->GetPosition().y };
}

void PhysicsBody::ApplyImpulse(sf::Vector2f _impulse)
{
	m_Body->ApplyLinearImpulseToCenter({ _impulse.x, _impulse.y}, true);
}

void PhysicsBody::SetShape(b2Shape* _shape)
{
	if (m_Shape)
		delete m_Shape;
	m_Shape = nullptr;
	m_Shape = _shape;
}

void PhysicsBody::SetBodyType(b2BodyType _bodyType)
{
	m_BodyType = _bodyType;
	SetupBody();
}

void PhysicsBody::SetPosition(sf::Vector2f _position)
{
	m_Position = _position;

	if (m_Body)
		m_Body->SetTransform({ m_Position.x / Helper::Scale, m_Position.y / Helper::Scale}, 0.0f);
}

sf::Vector2f PhysicsBody::GetPosition()
{
	return m_Position;
}

void PhysicsBody::SetSize(sf::Vector2f _size)
{
	m_Size = _size;
	SetupBody();
}

void PhysicsBody::DestroyBody()
{
	if (m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}

void PhysicsBody::SetupBody()
{
	DestroyBody();

	b2BodyDef bodyDef;
	bodyDef.allowSleep = true;
	bodyDef.type = m_BodyType;
	bodyDef.bullet = true;
	bodyDef.position = b2Vec2(m_Position.x / Helper::Scale, m_Position.y / Helper::Scale);
	m_Body = m_World->CreateBody(&bodyDef);

	b2PolygonShape* polygonShape  = dynamic_cast<b2PolygonShape*>(m_Shape);
	if (polygonShape != nullptr)
		polygonShape->SetAsBox((m_Size.x / 2) / Helper::Scale, (m_Size.y / 2) / Helper::Scale);
	else
	{
		b2CircleShape* circleShape = dynamic_cast<b2CircleShape*>(m_Shape);
		if (circleShape != nullptr)
			circleShape->m_radius = m_Size.x / Helper::Scale;
	}

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = m_Shape;
	fixtureDef.restitution = 0.6f;
	m_Body->CreateFixture(&fixtureDef);
}
