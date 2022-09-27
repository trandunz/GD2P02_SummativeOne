// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PhysicsBody.cpp 
// Description  : PhysicsBody Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape, b2BodyType _bodyType, float _density, float _restitution)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	m_BodyShape = _shape;
	m_Density = _density;
	SetupBody();
}

PhysicsBody::PhysicsBody(b2World& _world, UserData& _userData, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape, b2BodyType _bodyType, float _density, float _restitution)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	m_BodyShape = _shape;
	m_Density = _density;
	SetupBody(_userData);
}

PhysicsBody::~PhysicsBody()
{
	DestroyBody();
	m_World = nullptr;
}

void PhysicsBody::Update()
{
	// Set rotation to that of the b2Body
	m_Rotation = m_Body->GetTransform().q.GetAngle();
	// Set position to that of the b2Body is pixel coords
	m_Position = Statics::Scale * sf::Vector2f{m_Body->GetPosition().x, m_Body->GetPosition().y};
}

void PhysicsBody::ApplyImpulse(sf::Vector2f _impulse)
{
	// Apply an impulse too the body
	m_Body->SetLinearVelocity(m_Body->GetLinearVelocity() + b2Vec2{ _impulse.x, _impulse.y });
}

void PhysicsBody::SetShape(BODYSHAPE _shape)
{
	m_BodyShape = _shape;
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
		m_Body->SetTransform({ m_Position.x / Statics::Scale, m_Position.y / Statics::Scale}, m_Rotation);
}

sf::Vector2f PhysicsBody::GetPosition()
{
	return m_Position;
}

void PhysicsBody::SetRotation(float _degrees)
{
	m_Rotation = _degrees * ((float)PI / 180.0f);

	if (m_Body)
		m_Body->SetTransform({ m_Position.x / Statics::Scale, m_Position.y / Statics::Scale }, m_Rotation);
}

float PhysicsBody::GetRotation()
{
	return m_Rotation;
}

b2Vec2 PhysicsBody::GetB2Position()
{
	if (m_Body != nullptr)
	{
		return m_Body->GetPosition();
	}
	return {};
}

sf::Vector2f PhysicsBody::GetVelocity()
{
	if (m_Body != nullptr)
	{
		return { m_Body->GetLinearVelocity().x * Statics::Scale,  m_Body->GetLinearVelocity().y * Statics::Scale };
	}
	return {};
}

void PhysicsBody::SetSize(sf::Vector2f _size)
{
	m_Size = _size;
	SetupBody();
}

b2Body* PhysicsBody::GetBody()
{
	return m_Body;
}

b2World* PhysicsBody::GetWorld()
{
	return m_World;
}

void PhysicsBody::DestroyJoints()
{
	if (m_Body != nullptr)
	{
		// loop over all joints and push them too the list to destroy
		std::vector<b2Joint*> jointsToDestroy{};
		for (auto jointEdge = m_Body->GetJointList(); jointEdge; jointEdge = jointEdge->next)
		{
			jointsToDestroy.push_back(jointEdge->joint);
		}
		// Loop over all joint pointers and destroy them
		for (auto& joint : jointsToDestroy)
		{
			if (joint != nullptr)
			{
				m_World->DestroyJoint(joint);
				joint = nullptr;
			}
		}
		// Clear the vector and make it size 0
		jointsToDestroy.clear();
		jointsToDestroy.resize(0);
	}
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

	// Define the bodys properties
	b2BodyDef bodyDef;
	bodyDef.allowSleep = true; // If body stops, dont do calculations
	bodyDef.type = m_BodyType; // Dynamic, static e.t.c
	bodyDef.bullet = false; // Is it moving very fast?
	bodyDef.position = b2Vec2(m_Position.x / Statics::Scale, m_Position.y / Statics::Scale);
	bodyDef.angularDamping = 2.0f; // Damp thee rotation
	m_Body = m_World->CreateBody(&bodyDef); // Create the body!

	b2Shape* shape{ nullptr };
	switch (m_BodyShape)
	{
	case BODYSHAPE::POLYGON:
	{
		b2PolygonShape polygonShape;
		// Set as a box the size of sprite
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CIRCLE:
	{
		b2CircleShape circleShape;
		// Set as circle the size of the sprite width
		circleShape.m_radius = (m_Size.x / 2.0f) / Statics::Scale;
		shape = new b2CircleShape(circleShape);
		break;
	}
	case BODYSHAPE::TRIANGLE:
	{
		b2PolygonShape polygonShape;
		// Create 3 vertices in an equalateral triangle
		std::vector<b2Vec2> vertices
		{
			{-(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{0, -(m_Size.y / 2) / Statics::Scale},
			{(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale}
		};
		polygonShape.Set(&vertices[0], (int32)vertices.size());
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CORNER:
	{
		b2PolygonShape polygonShape;
		// Create 3 vertices in a right angle triangle
		std::vector<b2Vec2> vertices
		{
			{(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{-(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{-(m_Size.x / 2.0f) / Statics::Scale, -(m_Size.y / 2) / Statics::Scale}
		};
		polygonShape.Set(&vertices[0], (int32)vertices.size());
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	default:
	{
		b2PolygonShape polygonShape;
		// Set as a box the size of the sprite
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	}

	// Define the fixtures properties
	b2FixtureDef fixtureDef;
	fixtureDef.density = m_Density; // Mass / area
	fixtureDef.shape = &*shape; // Set the shape
	fixtureDef.restitution = 0.3f; // Bouncyness?
	m_Body->CreateFixture(&fixtureDef); // Create the fixture!
	m_Body->SetFixedRotation(false); // Dont fix the rotation

	// Cleanup the shape because fixtureDef copys it so no need to keep a reference
	if (shape != nullptr)
	{
		delete shape;
		shape = nullptr;
	}
}

void PhysicsBody::SetupBody(UserData& _userData)
{
	DestroyBody();

	// Define the bodys properties
	b2BodyDef bodyDef;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&_userData); // Assign user data
	bodyDef.allowSleep = true; // If body stops, dont do calculations
	bodyDef.type = m_BodyType; // Dynamic, static e.t.c
	bodyDef.bullet = false; // Is it moving very fast?
	bodyDef.position = b2Vec2(m_Position.x / Statics::Scale, m_Position.y / Statics::Scale);
	bodyDef.angularDamping = 2.0f; // Damp thee rotation
	m_Body = m_World->CreateBody(&bodyDef); // Create the body!

	b2Shape* shape{ nullptr };
	switch (m_BodyShape)
	{
	case BODYSHAPE::POLYGON:
	{
		b2PolygonShape polygonShape;
		// Set as a box the size of sprite
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CIRCLE:
	{
		b2CircleShape circleShape;
		// Set as circle the size of the sprite width
		circleShape.m_radius = (m_Size.x / 2.0f) / Statics::Scale;
		shape = new b2CircleShape(circleShape);
		break;
	}
	case BODYSHAPE::TRIANGLE:
	{
		b2PolygonShape polygonShape;
		// Create 3 vertices in an equalateral triangle
		std::vector<b2Vec2> vertices
		{
			{-(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{0, -(m_Size.y / 2) / Statics::Scale},
			{(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale}
		};
		polygonShape.Set(&vertices[0], (int32)vertices.size());
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CORNER:
	{
		b2PolygonShape polygonShape;
		// Create 3 vertices in a right angle triangle
		std::vector<b2Vec2> vertices
		{
			{(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{-(m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale},
			{-(m_Size.x / 2.0f) / Statics::Scale, -(m_Size.y / 2) / Statics::Scale}
		};
		polygonShape.Set(&vertices[0], (int32)vertices.size());
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	default:
	{
		b2PolygonShape polygonShape;
		// Set as a box the size of the sprite
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	}

	// Define the fixtures properties
	b2FixtureDef fixtureDef;
	fixtureDef.density = m_Density; // Mass / area
	fixtureDef.shape = &*shape; // Set the shape
	fixtureDef.restitution = 0.3f; // Bouncyness?
	m_Body->CreateFixture(&fixtureDef); // Create the fixture!
	m_Body->SetFixedRotation(false); // Dont fix the rotation

	// Cleanup the shape because fixtureDef copys it so no need to keep a reference
	if (shape != nullptr)
	{
		delete shape;
		shape = nullptr;
	}
}
