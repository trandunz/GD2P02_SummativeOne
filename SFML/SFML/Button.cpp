#include "Button.h"

Button::Button(std::string _label, sf::Vector2f _position, std::function<void()> _onPressLambda)
{
	m_Label.setString(_label);
	Helper::SetOriginCentre(m_Label);
	SetTexture("Button.png");
	SetPosition(_position);
	m_OnPressFunction = _onPressLambda;
}

Button::~Button()
{
	m_OnPressFunction = nullptr;
}

void Button::CallOnPress()
{
	if (m_OnPressFunction)
	{
		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(Helper::RenderWindow).x, (float)sf::Mouse::getPosition(Helper::RenderWindow).y };
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

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_Label);
}

void Button::SetTexture(std::string _fileName)
{
	m_Texture.loadFromFile("Resources/Sprites/" + _fileName);
	m_Sprite.setTexture(m_Texture, true);
	Helper::SetOriginCentre(m_Sprite);
}
