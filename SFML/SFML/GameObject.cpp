#include "GameObject.h"

GameObject::GameObject(b2World& _world, sf::Vector2f _startPos)
{
	m_World = &_world;

	SetTexture("Ball.png");

	m_Mesh.setPosition(_startPos);
	m_Mesh.setColor(sf::Color::White);

	//m_PhysicsBody = new PhysicsBody
	//(
	//	*m_World,
	//	{ m_Mesh.getLocalBounds().width,m_Mesh.getLocalBounds().height }, // Size
	//	{ m_Mesh.getPosition().x, m_Mesh.getPosition().y } // Pos
	//);
}

GameObject::~GameObject()
{
	if (m_PhysicsBody)
		delete m_PhysicsBody;
	m_PhysicsBody = nullptr;
	m_World = nullptr;
}

void GameObject::DeleteBody()
{
	if (m_PhysicsBody)
		delete m_PhysicsBody;
	m_PhysicsBody = nullptr;
}

void GameObject::SetPosition(sf::Vector2f _position)
{
	m_Mesh.setPosition(_position);

	if (m_PhysicsBody)
		m_PhysicsBody->SetPosition(_position);
}

void GameObject::SetTexture(std::string _fileName)
{
	m_Texture.loadFromFile("Resources/Sprites/" + _fileName);
	m_Mesh.setTexture(m_Texture, true);
	Helper::SetOriginCentre(m_Mesh);
	if (m_PhysicsBody)
	{
		m_PhysicsBody->SetSize({ m_Mesh.getLocalBounds().width,m_Mesh.getLocalBounds().height });
	}
}

void GameObject::SetBodyType(b2BodyType _bodyType)
{
	if (m_PhysicsBody)
		m_PhysicsBody->SetBodyType(_bodyType);
}

void GameObject::Start()
{
}

void GameObject::Update()
{
	if (m_PhysicsBody)
	{
		m_Mesh.setPosition(m_PhysicsBody->GetPosition());
	}
}

void GameObject::Launch(sf::Vector2f _impulse)
{
	if (m_PhysicsBody)
		delete m_PhysicsBody;
	m_PhysicsBody = nullptr;

	m_PhysicsBody = new PhysicsBody
	(
		*m_World,
		{ m_Mesh.getLocalBounds().width,m_Mesh.getLocalBounds().height }, // Size
		{ m_Mesh.getPosition().x, m_Mesh.getPosition().y } // Pos
	);

	m_PhysicsBody->ApplyImpulse(_impulse);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Mesh);
}
