#pragma once
#include "PhysicsBody.h"

class GameObject : public sf::Drawable
{
public:
	GameObject(b2World& _world, sf::Vector2f _startPos);
	virtual ~GameObject();

	void DeleteBody();

	void SetPosition(sf::Vector2f _position);

	void SetTexture(std::string _location);
	void SetBodyType(b2BodyType _bodyType);

	void Start();
	void Update();

	// temp
	void Launch(sf::Vector2f _impulse);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	b2World* m_World = nullptr;
	PhysicsBody* m_PhysicsBody = nullptr;
	sf::Sprite m_Mesh;
	sf::Texture m_Texture;
};

