#pragma once
#include "PhysicsBody.h"
#include "Mesh.h"

class GameObject : public sf::Drawable
{
public:
	GameObject(b2World& _world, sf::Vector2f _startPos);
	virtual ~GameObject();

	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);;

	void SetTexture(std::string _location);
	void SetShapeType(b2Shape* _shapeType);
	void SetBodyType(b2BodyType _bodyType);

	void Start();
	void Update();

	void CreateBody();
	void DestroyBody();

	void Launch(sf::Vector2f _impulse);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	b2World* m_World = nullptr;
	b2Shape* m_ShapeType = nullptr;
	b2BodyType m_BodyType = b2_staticBody;
	PhysicsBody* m_PhysicsBody = nullptr;
	Mesh* m_Mesh = nullptr;
};

