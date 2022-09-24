// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PhysicsBody.h 
// Description  : PhysicsBody Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

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
	/// <summary>
	/// Constucts a PhysicsBody
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_startPos"></param>
	/// <param name="_size"></param>
	/// <param name="_shape"></param>
	/// <param name="_bodyType"></param>
	/// <param name="_density"></param>
	/// <param name="_restitution"></param>
	PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape = BODYSHAPE::POLYGON, b2BodyType _bodyType = b2_staticBody, float _density = 1.0f, float _restitution = 1.0f);
	/// <summary>
	/// Constucts a PhysicsBody
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_userData"></param>
	/// <param name="_startPos"></param>
	/// <param name="_size"></param>
	/// <param name="_shape"></param>
	/// <param name="_bodyType"></param>
	/// <param name="_density"></param>
	/// <param name="_restitution"></param>
	PhysicsBody(b2World& _world, UserData& _userData, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape = BODYSHAPE::POLYGON, b2BodyType _bodyType = b2_staticBody, float _density = 1.0f, float _restitution = 1.0f);
	/// <summary>
	/// PhysicsBody Destructor
	/// </summary>
	~PhysicsBody();

	/// <summary>
	/// Updates the physics body
	/// </summary>
	void Update();

	/// <summary>
	/// Apply's an impulse too the physics Body
	/// </summary>
	/// <param name="_impulse"></param>
	void ApplyImpulse(sf::Vector2f _impulse);

	/// <summary>
	/// Destroys The Attached Joints
	/// </summary>
	void DestroyJoints();
private:
	/// <summary>
	/// Cleans up the b2Body
	/// </summary>
	void DestroyBody();

	/// <summary>
	/// Creates a b2Body With Userdata
	/// </summary>
	/// <param name="_userData"></param>
	void SetupBody(UserData& _userData);
	/// <summary>
	/// Creates a b2Body
	/// </summary>
	void SetupBody();

	sf::Vector2f m_Size{};
	b2BodyType m_BodyType = b2_staticBody;
	b2World* m_World = nullptr;
	sf::Vector2f m_Position{};
	float m_Rotation{};
	float m_Density{ 1.0f };
	b2Body* m_Body = nullptr;
	BODYSHAPE m_BodyShape{ BODYSHAPE::POLYGON };

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition();

	void SetRotation(float _degrees);
	float GetRotation();

	b2Vec2 GetB2Position();

	sf::Vector2f GetVelocity();

	void SetSize(sf::Vector2f _size);

	b2Body* GetBody();

	b2World* GetWorld();

	void SetShape(BODYSHAPE _shape);

	void SetBodyType(b2BodyType _bodyType);
};