#include "Mesh.h"

Mesh::Mesh(std::string _spriteName, sf::Vector2f _position, sf::Vector2f _scale)
{
	SetTexture(_spriteName);
	m_Sprite.setScale(_scale);
	m_Sprite.setPosition(_position);
}

Mesh::~Mesh()
{
}

void Mesh::SetTexture(std::string _spriteName)
{
	m_Texture.loadFromFile("Resources/Sprites/" + _spriteName);
	m_Sprite.setTexture(m_Texture, true);
	Helper::SetOriginCentre(m_Sprite);
}

void Mesh::SetPosition(sf::Vector2f _position)
{
	m_Sprite.setPosition(_position);
}

sf::FloatRect Mesh::GetLocalBounds()
{
	return m_Sprite.getLocalBounds();
}

void Mesh::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
