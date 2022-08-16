#pragma once
#include "box2d/box2d.h"
#include "Statics.h"
#include "Math.h"

class PhysicsBody
{
public:
	PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape = nullptr, b2BodyType _bodyType = b2_staticBody, float _restitution = 0.0f, float _density = 1.0f);
	template<typename T>
	PhysicsBody(b2World& _world, T* _userData, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape = nullptr, b2BodyType _bodyType = b2_staticBody, float _restitution = 0.0f, float _density = 1.0f);
	~PhysicsBody();

	void Update();

	void ApplyImpulse(sf::Vector2f _impulse);

	void SetShape(b2Shape* _shape);
	void SetBodyType(b2BodyType _bodyType);

	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();
	b2Vec2 GetB2Position();

	void SetSize(sf::Vector2f _size);

private:
	void DestroyBody();

	template<typename T>
	void SetupBody(T* _userData = nullptr);
	void SetupBody();

	sf::Vector2f m_Size{};
	b2BodyType m_BodyType = b2_staticBody;
	b2World* m_World = nullptr;
	sf::Vector2f m_Position{};
	b2Shape* m_Shape = nullptr;
	b2Body* m_Body = nullptr;
};

template<typename T>
PhysicsBody::PhysicsBody(b2World& _world, T* _userData, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape, b2BodyType _bodyType, float _restitution, float _density)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	if (_shape == nullptr)
		m_Shape = new b2PolygonShape();
	else
		m_Shape = _shape;
	SetupBody(_userData);
}

template<typename T>
void PhysicsBody::SetupBody(T* _userData)
{
	DestroyBody();

	b2BodyDef bodyDef;
	bodyDef.allowSleep = true;
	bodyDef.type = m_BodyType;
	bodyDef.bullet = true;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(_userData);
	bodyDef.position = b2Vec2(m_Position.x / Statics::Scale, m_Position.y / Statics::Scale);
	m_Body = m_World->CreateBody(&bodyDef);

	b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>(m_Shape);
	if (polygonShape != nullptr)
	{
		polygonShape->SetAsBox((m_Size.x / 2) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		polygonShape = nullptr;
	}
	else
	{
		b2CircleShape* circleShape = dynamic_cast<b2CircleShape*>(m_Shape);
		if (circleShape != nullptr)
		{
			circleShape->m_radius = (m_Size.x / 2) / Statics::Scale;
			circleShape->m_p.SetZero();
		}
		circleShape = nullptr;
	}

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = m_Shape;
	fixtureDef.restitution = 0.6f;
	m_Body->CreateFixture(&fixtureDef);
}