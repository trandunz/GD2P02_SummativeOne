#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(b2World& _world, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape, b2BodyType _bodyType, float _restitution, float _density)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	m_BodyShape = _shape;
	SetupBody();
}

PhysicsBody::PhysicsBody(b2World& _world, UserData& _userData, sf::Vector2f _startPos, sf::Vector2f _size, BODYSHAPE _shape, b2BodyType _bodyType, float _restitution, float _density)
{
	m_World = &_world;
	m_Position = _startPos;
	m_Size = _size;
	m_BodyType = _bodyType;
	m_BodyShape = _shape;
	SetupBody(_userData);
}

PhysicsBody::~PhysicsBody()
{
	DestroyBody();
	m_World = nullptr;
}

void PhysicsBody::Update()
{
	m_Rotation = m_Body->GetTransform().q.GetAngle();
	m_Position = Statics::Scale * sf::Vector2f{m_Body->GetPosition().x, m_Body->GetPosition().y};
}

void PhysicsBody::ApplyImpulse(sf::Vector2f _impulse)
{
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
		std::vector<b2Joint*> jointsToDestroy{};
		for (auto jointEdge = m_Body->GetJointList(); jointEdge; jointEdge = jointEdge->next)
		{
			jointsToDestroy.push_back(jointEdge->joint);
		}
		for (auto& joint : jointsToDestroy)
		{
			if (joint != nullptr)
			{
				m_World->DestroyJoint(joint);
				joint = nullptr;
			}
		}
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

	b2BodyDef bodyDef;
	bodyDef.allowSleep = true;
	bodyDef.type = m_BodyType;
	bodyDef.bullet = false;
	bodyDef.position = b2Vec2(m_Position.x / Statics::Scale, m_Position.y / Statics::Scale);
	m_Body = m_World->CreateBody(&bodyDef);

	b2Shape* shape{ nullptr };
	switch (m_BodyShape)
	{
	case BODYSHAPE::POLYGON:
	{
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CIRCLE:
	{
		b2CircleShape circleShape;
		circleShape.m_radius = (m_Size.x / 2.0f) / Statics::Scale;
		shape = new b2CircleShape(circleShape);
		break;
	}
	default:
	{
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	}

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &*shape;
	fixtureDef.restitution = 0.6f;
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetFixedRotation(false);

	if (shape != nullptr)
	{
		delete shape;
		shape = nullptr;
	}
}

void PhysicsBody::SetupBody(UserData& _userData)
{
	DestroyBody();

	b2BodyDef bodyDef;
	bodyDef.allowSleep = true;
	bodyDef.type = m_BodyType;
	bodyDef.bullet = false;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&_userData);
	bodyDef.position = b2Vec2(m_Position.x / Statics::Scale, m_Position.y / Statics::Scale);
	m_Body = m_World->CreateBody(&bodyDef);
	
	b2Shape* shape{ nullptr };
	switch (m_BodyShape)
	{
	case BODYSHAPE::POLYGON:
	{
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	case BODYSHAPE::CIRCLE:
	{
		b2CircleShape circleShape;
		circleShape.m_radius = (m_Size.x / 2.0f) / Statics::Scale;
		shape = new b2CircleShape(circleShape);
		break;
	}
	default:
	{
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox((m_Size.x / 2.0f) / Statics::Scale, (m_Size.y / 2) / Statics::Scale);
		shape = new b2PolygonShape(polygonShape);
		break;
	}
	}

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &*shape;
	fixtureDef.restitution = 0.6f;
	m_Body->CreateFixture(&fixtureDef);
	m_Body->SetFixedRotation(false);

	if (shape != nullptr)
	{
		delete shape;
		shape = nullptr;
	}
}
