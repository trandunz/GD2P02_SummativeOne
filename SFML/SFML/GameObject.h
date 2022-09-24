// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: GameObject.h 
// Description  : GameObject Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "PhysicsBody.h"
#include "Mesh.h"

class GameObject : public sf::Drawable
{
public:
	GameObject(b2World& _world, sf::Vector2f _startPos);
	/// <summary>
	/// GameObject Destructor
	/// </summary>
	virtual ~GameObject();

	virtual void Start();
	virtual void Update();

	virtual void CreateBody();
	void DestroyBody();

	bool Destroy = false;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	float m_Mass{ 1.0f };
	UserData m_b2UserData;
	b2World* m_World = nullptr;
	BODYSHAPE m_BodyShape = BODYSHAPE::POLYGON;
	b2BodyType m_BodyType = b2_staticBody;
	PhysicsBody* m_PhysicsBody = nullptr;
	Mesh* m_Mesh = nullptr;

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	b2Body* GetBody();

	PhysicsBody* GetPhysicsBody();

	b2Vec2 GetBodyPosition();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f _position);

	sf::Vector2f GetVelocity();

	void SetRotation(float _degrees);

	void SetScale(sf::Vector2f _scale);

	void SetTexture(std::string _location);

	void SetShapeType(BODYSHAPE _shapeType);

	void SetBodyType(b2BodyType _bodyType);
};

