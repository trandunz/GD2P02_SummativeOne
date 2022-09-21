#pragma once
#include "PhysicsBody.h"
#include "Mesh.h"

class GameObject : public sf::Drawable
{
public:
	GameObject(b2World& _world, sf::Vector2f _startPos);
	virtual ~GameObject();

	b2Body* GetBody();
	b2Vec2 GetBodyPosition();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	void SetPosition(sf::Vector2f _position);
	void SetRotation(float _degrees);
	void SetScale(sf::Vector2f _scale);;

	void SetTexture(std::string _location);
	void SetShapeType(BODYSHAPE _shapeType);
	void SetBodyType(b2BodyType _bodyType);

	virtual void Start();
	virtual void Update();

	void CreateBody();
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
};

