#include "GameObject.h"

GameObject::GameObject(b2World& _world, sf::Vector2f _startPos)
{
	m_World = &_world;
	m_Mesh = new Mesh("Wood/Plank (1).png");
	m_Mesh->SetPosition(_startPos);
}

GameObject::~GameObject()
{
	DestroyBody();
	m_World = nullptr;

	m_ShapeType = nullptr;

	if (m_Mesh)
		delete m_Mesh;
	m_Mesh = nullptr;
}

void GameObject::SetPosition(sf::Vector2f _position)
{
	m_Mesh->SetPosition(_position);

	if (m_PhysicsBody != nullptr)
		m_PhysicsBody->SetPosition(_position);
}

void GameObject::SetScale(sf::Vector2f _scale)
{
	m_Mesh->SetScale(_scale);
}

void GameObject::SetTexture(std::string _fileName)
{
	m_Mesh->SetTexture(_fileName);
	if (m_PhysicsBody != nullptr)
	{
		m_PhysicsBody->SetSize({ m_Mesh->GetLocalBounds().width,m_Mesh->GetLocalBounds().height });
	}
}

void GameObject::SetShapeType(b2Shape* _shapeType)
{
	if (m_ShapeType)
		delete m_ShapeType;
	m_ShapeType = nullptr;
	m_ShapeType = _shapeType;
}

void GameObject::SetBodyType(b2BodyType _bodyType)
{
	m_BodyType = _bodyType;

	if (m_PhysicsBody != nullptr)
		m_PhysicsBody->SetBodyType(_bodyType);
}

void GameObject::Start()
{
}

void GameObject::Update()
{
	if (m_PhysicsBody != nullptr)
	{
		m_PhysicsBody->Update();
		m_Mesh->SetPosition(m_PhysicsBody->GetPosition());
	}
}

void GameObject::Launch(sf::Vector2f _impulse)
{
	CreateBody();
	m_PhysicsBody->ApplyImpulse(_impulse);
}

void GameObject::CreateBody()
{
	DestroyBody();
	m_PhysicsBody = new PhysicsBody
	(
		*m_World,
		m_Mesh->GetPosition(), // Size
		{ m_Mesh->GetGlobalBounds().width,m_Mesh->GetGlobalBounds().height }, // Pos
		m_ShapeType,
		m_BodyType
	);
}

void GameObject::DestroyBody()
{
	if (m_PhysicsBody != nullptr)
	{
		delete m_PhysicsBody;
		m_PhysicsBody = nullptr;
		m_ShapeType = nullptr;
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_Mesh);
}
