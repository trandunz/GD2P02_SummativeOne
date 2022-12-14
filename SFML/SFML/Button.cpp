// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Button.cpp 
// Description  : Button Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "Button.h"
#include "TextureLoader.h"
#include "Math.h"

Button::Button(ButtonProperties _properties)
{
	m_Properties = _properties;

	m_Label.setFont(Statics::TimesNewRoman);
	m_Label.setCharacterSize(24);

	m_Label.setString(_properties.Label);

	m_Label.setFillColor(sf::Color::Black);

	// Set texture if one was given in properties
	if (_properties.Texture == nullptr)
		SetTexture("GUI/Button.png");
	else
		SetTexture(*_properties.Texture);

	SetScale(_properties.Scale);
	SetPosition(_properties.Position);
}

Button::~Button()
{
	m_Properties.OnPressLambda = nullptr;
}

void Button::CallOnPress()
{
	if (m_Properties.OnPressLambda != nullptr)
	{
		// Check if mouse position is over the sprite
		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(Statics::RenderWindow).x, (float)sf::Mouse::getPosition(Statics::RenderWindow).y };
		if (m_Sprite.getGlobalBounds().contains(mousePos))
		{
			m_Properties.OnPressLambda();
		}
	}
}

void Button::SetLabel(std::string _newLabel)
{
	m_Label.setString(_newLabel);
}

void Button::SetPosition(sf::Vector2f _position)
{
	m_Sprite.setPosition(_position);
	m_Label.setPosition(_position);
}

void Button::SetScale(sf::Vector2f _scale)
{
	m_Sprite.setScale(_scale);
	m_Label.setCharacterSize(m_Label.getCharacterSize() * (unsigned)Mag(_scale));
	SetOriginCentre(m_Label);
}

void Button::ResetScale()
{
	m_Sprite.setScale(m_Properties.Scale);
	m_Label.setCharacterSize(m_Label.getCharacterSize() * (unsigned)Mag(m_Properties.Scale));
	SetOriginCentre(m_Label);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_Label);

}

void Button::SetTexture(std::string _fileName)
{
	m_Sprite.setTexture(TextureLoader::LoadTexture(_fileName), true);
	SetOriginCentre(m_Sprite);
}

void Button::SetTexture(sf::Texture& _texture)
{
	m_Sprite.setTexture(_texture);
	SetOriginCentre(m_Sprite);
}
