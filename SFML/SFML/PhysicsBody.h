#pragma once
#include "box2d/box2d.h"
#include "Helper.h"

class PhysicsBody
{
public:
	PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, b2BodyType _bodyType = b2_staticBody, float _restitution = 0.0f, float _density = 1.0f);
	~PhysicsBody();

	void Update();

	void ApplyImpulse(sf::Vector2f _impulse);

	void SetBodyType(b2BodyType _bodyType);

	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();

	void SetSize(sf::Vector2f _size);

private:
	void DestroyBody();
	void SetupBody();

	sf::Vector2f m_Size{};
	b2BodyType m_BodyType = b2_staticBody;
	b2World* m_World = nullptr;
	sf::Vector2f m_Position{};
	b2Body* m_Body = nullptr;
};

