#pragma once
#include "Statics.h"
#include "Math.h"

class Mesh : public sf::Drawable
{
public:
	Mesh(std::string _spriteName, sf::Vector2f _position = { 0,0 }, sf::Vector2f _scale = { 1,1 });
	~Mesh();

	void SetTexture(std::string _spriteName);
	void SetScale(sf::Vector2f _scale);
	void SetPosition(sf::Vector2f _position);
	void SetRotation(float _radians);
	inline sf::Vector2f GetPosition() {return m_Sprite.getPosition();}
	sf::FloatRect GetLocalBounds();
	sf::FloatRect GetGlobalBounds();
	sf::Vector2f GetSize();
	float GetRotation();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite m_Sprite;
};

