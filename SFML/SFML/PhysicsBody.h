#pragma once
#include "box2d/box2d.h"
#include "Statics.h"
#include "Math.h"

enum class BODYSHAPE
{
	POLYGON,
	CIRCLE,
	TRIANGLE,
	CORNER
};

class PhysicsBody
{
public:
	PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape = BODYSHAPE::POLYGON, b2BodyType _bodyType = b2_staticBody, float _density = 1.0f, float _restitution = 1.0f);
	PhysicsBody(b2World& _world, UserData& _userData, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape = BODYSHAPE::POLYGON, b2BodyType _bodyType = b2_staticBody, float _density = 1.0f, float _restitution = 1.0f);
	~PhysicsBody();

	void Update();

	void ApplyImpulse(sf::Vector2f _impulse);

	void SetShape(BODYSHAPE _shape);
	void SetBodyType(b2BodyType _bodyType);

	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();
	void SetRotation(float _degrees);
	float GetRotation();
	b2Vec2 GetB2Position();

	sf::Vector2f GetVelocity();

	void SetSize(sf::Vector2f _size);

	b2Body* GetBody();
	b2World* GetWorld();

	void DestroyJoints();
private:
	void DestroyBody();

	void SetupBody(UserData& _userData);
	void SetupBody();

	sf::Vector2f m_Size{};
	b2BodyType m_BodyType = b2_staticBody;
	b2World* m_World = nullptr;
	sf::Vector2f m_Position{};
	float m_Rotation{};
	float m_Density{ 1.0f };
	b2Body* m_Body = nullptr;
	BODYSHAPE m_BodyShape{ BODYSHAPE::POLYGON };
};