#include "Mesh.h"
#include "TextureLoader.h"

Mesh::Mesh(std::string _spriteName, sf::Vector2f _position, sf::Vector2f _scale)
{
	SetTexture(_spriteName);
	m_Sprite.setScale(_scale);
	SetOriginCentre(m_Sprite);
	m_Sprite.setPosition(_position);
}

Mesh::~Mesh()
{
}

void Mesh::SetTexture(std::string _spriteName)
{
	m_Sprite.setTexture(TextureLoader::LoadTexture(_spriteName), true);
	SetOriginCentre(m_Sprite);
}

void Mesh::SetScale(sf::Vector2f _scale)
{
	m_Sprite.setScale(_scale);
}

void Mesh::SetPosition(sf::Vector2f _position)
{
	m_Sprite.setPosition(_position);
}

sf::FloatRect Mesh::GetLocalBounds()
{
	return m_Sprite.getLocalBounds();
}

sf::FloatRect Mesh::GetGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

void Mesh::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
