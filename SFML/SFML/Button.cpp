#include "Button.h"
#include "TextureLoader.h"

Button::Button(std::string _label, sf::Vector2f _position, callback_function _onPressLambda, sf::Vector2f _scale)
{
	m_Label.setFont(Statics::TimesNewRoman);
	m_Label.setString(_label);
	m_Label.setCharacterSize(24); 
	m_Label.setFillColor(sf::Color::Black);
	SetTexture("Button.png");
	SetScale(_scale);
	SetPosition(_position);
	m_OnPressFunction = _onPressLambda;
}

Button::~Button()
{
	m_OnPressFunction = nullptr;
}

void Button::CallOnPress()
{
	if (m_OnPressFunction != nullptr)
	{
		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(Statics::RenderWindow).x, (float)sf::Mouse::getPosition(Statics::RenderWindow).y };
		if (m_Sprite.getGlobalBounds().contains(mousePos))
		{
			m_OnPressFunction();
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
