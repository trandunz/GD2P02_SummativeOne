#pragma once
#include "box2d/box2d.h"
#include "Statics.h"
#include "Math.h"

class PhysicsBody
{
public:
	PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape = nullptr, b2BodyType _bodyType = b2_staticBody, float _restitution = 0.0f, float _density = 1.0f);
	PhysicsBody(b2World& _world, UserData& _userData, sf::Vector2f _startPos, sf::Vector2f _size, b2Shape* _shape = nullptr, b2BodyType _bodyType = b2_staticBody, float _restitution = 0.0f, float _density = 1.0f);
	~PhysicsBody();

	void Update();

	void ApplyImpulse(sf::Vector2f _impulse);

	void SetShape(b2Shape* _shape);
	void SetBodyType(b2BodyType _bodyType);

	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();
	void SetRotation(float _degrees);
	float GetRotation();
	b2Vec2 GetB2Position();

	void SetSize(sf::Vector2f _size);

	b2Body* GetBody();
	b2World* GetWorld();

private:
	void DestroyBody();

	void SetupBody(UserData& _userData);
	void SetupBody();

	sf::Vector2f m_Size{};
	b2BodyType m_BodyType = b2_staticBody;
	b2World* m_World = nullptr;
	sf::Vector2f m_Position{};
	float m_Rotation{};
	b2Shape* m_Shape = nullptr;
	b2Body* m_Body = nullptr;
};