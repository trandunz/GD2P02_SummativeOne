#include "GameObject.h"

GameObject::GameObject(b2World& _world, sf::Vector2f _startPos)
{
	m_World = &_world;
	m_Mesh = new Mesh("Wood/Plank (1).png");
	m_Mesh->SetPosition(_startPos);
	m_b2UserData = UserData();
	m_b2UserData.identifier = "GameObject";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);
}

GameObject::~GameObject()
{
	DestroyBody();
	m_World = nullptr;

	if (m_Mesh)
		delete m_Mesh;
	m_Mesh = nullptr;
}

b2Body* GameObject::GetBody()
{
	if (m_PhysicsBody != nullptr)
	{
		return m_PhysicsBody->GetBody();
	}
	else
	{
		return nullptr;
	}
}

b2Vec2 GameObject::GetBodyPosition()
{
	if (m_PhysicsBody != nullptr)
		return m_PhysicsBody->GetB2Position();
	else
		return {};
}

sf::Vector2f GameObject::GetPosition()
{
	return m_Mesh->GetPosition();
}

void GameObject::SetPosition(sf::Vector2f _position)
{
	m_Mesh->SetPosition(_position);

	if (m_PhysicsBody != nullptr)
		m_PhysicsBody->SetPosition(_position);
}

void GameObject::SetRotation(float _degrees)
{
	if (m_PhysicsBody != nullptr)
	{
		m_PhysicsBody->SetRotation(_degrees);
	}
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

void GameObject::SetShapeType(BODYSHAPE _shapeType)
{
	m_BodyShape = _shapeType;
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
		m_Mesh->SetRotation(m_PhysicsBody->GetRotation());
	}
}

void GameObject::CreateBody()
{
	DestroyBody();
	m_PhysicsBody = new PhysicsBody
	(
		*m_World,
		m_b2UserData,
		m_Mesh->GetPosition(), // Pos
		{ m_Mesh->GetGlobalBounds().width,m_Mesh->GetGlobalBounds().height }, // Size
		m_BodyShape,
		m_BodyType
	);
}

void GameObject::DestroyBody()
{
	if (m_PhysicsBody != nullptr)
	{
		delete m_PhysicsBody;
		m_PhysicsBody = nullptr;
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_Mesh);
}
