#pragma once
#include "GameObject.h"

class Catapult : public sf::Drawable
{
public:
	Catapult(sf::Vector2f _position);
	~Catapult();

	void LoadBird(GameObject& _bird);
	void MoveBird();
	void ReleaseBird();

private:
	void SetTexture(std::string _fileName);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float m_LaunchStrength = 2.0f;

	GameObject* m_LoadedBird = nullptr;
	sf::Sprite m_Mesh;
	sf::Texture m_Texture;

	sf::Vector2f m_FirePosition;
	sf::Vector2f m_FireVector;
};

