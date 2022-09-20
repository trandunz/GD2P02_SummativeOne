#include "GUI.h"
#include "Math.h"
#include "Button.h"
#include "Utility.h"

void GUI::CleanupImageElement(std::string _key)
{
	auto it = m_vecImages.find(_key);
	if (it != m_vecImages.end())
	{
		it = m_vecImages.erase(it);
	}
}

void GUI::CleanupButtonElement(std::string _key)
{
	auto it = m_vecButtons.find(_key);
	if (it != m_vecButtons.end())
	{
		it = m_vecButtons.erase(it);
	}
}

void GUI::CleanupTextElement(std::string _key)
{
	auto it = m_vecTexts.find(_key);
	if (it != m_vecTexts.end())
	{
		it = m_vecTexts.erase(it);
	}
}

void GUI::CleanupElements()
{
	CleanupMap(m_vecTexts);
	CleanupMap(m_vecImages);
	CleanupMap(m_vecButtons);
}

void GUI::CreateButton(std::string _key, ButtonProperties _properties)
{
	m_vecButtons.insert_or_assign(_key, Button(_properties));
}

Button* GUI::GetButton(std::string _key)
{
	if (m_vecButtons.contains(_key))
		return &m_vecButtons[_key];
	else
		return nullptr;
}

void GUI::ResetAllButtonsScale()
{
	for (auto& button : m_vecButtons)
	{
		button.second.ResetScale();
	}
}

void GUI::CreateText(std::string _key, TextProperties _properties)
{
	m_vecTexts.insert_or_assign(_key, sf::Text());
	m_vecTexts[_key].setFont(Statics::TimesNewRoman);
	m_vecTexts[_key].setCharacterSize(_properties.iCharacterSize);
	m_vecTexts[_key].setFillColor(_properties.FillColor);
	m_vecTexts[_key].setOutlineColor(_properties.OutlineColor);
	m_vecTexts[_key].setOutlineThickness(1.0f);
	m_vecTexts[_key].setString(_properties.String);
	SetOriginCentre(m_vecTexts[_key]);
	m_vecTexts[_key].setPosition(_properties.StartPos);
}

sf::Text& GUI::GetText(std::string _key)
{
	return m_vecTexts[_key];
}

void GUI::SetText(std::string _key, std::string _value)
{
	m_vecTexts[_key].setString(_value);
	SetOriginCentre(m_vecTexts[_key]);
}

void GUI::AppendText(std::string _key, std::string _value)
{
	m_vecTexts[_key].setString(m_vecTexts[_key].getString() + _value);
	SetOriginCentre(m_vecTexts[_key]);
}

void GUI::CreateImage(std::string _key, ImageProperties _properties)
{
	m_vecImages.insert_or_assign(_key, sf::Sprite());
	m_vecImages[_key].setTexture(*_properties.Texture, true);
	m_vecImages[_key].setScale(_properties.Scale);
	SetOriginCentre(m_vecImages[_key]);
	m_vecImages[_key].setPosition(_properties.StartPos);
	m_vecImages[_key].setRotation(_properties.Rotation);
}

sf::Sprite& GUI::GetImage(std::string _key)
{
	return m_vecImages[_key];
}

void GUI::SetImageSprite(std::string _key, sf::Texture& _texture)
{
	m_vecImages[_key].setTexture(_texture, true);
	SetOriginCentre(m_vecImages[_key]);
}

void GUI::PollEvents()
{
	if (Statics::EventHandle.type == sf::Event::MouseButtonReleased
		&& Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
	{
		for (auto& button : m_vecButtons)
		{
			button.second.CallOnPress();
		}
	}
}

void GUI::Update()
{
	m_UIView.setSize(Statics::RenderWindow.getDefaultView().getSize());
	m_UIView.setCenter(Statics::RenderWindow.getDefaultView().getCenter());
}

void GUI::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.setView(m_UIView);

	for (auto& image : m_vecImages)
	{
		_target.draw(image.second);
	}
	for (auto& text : m_vecTexts)
	{
		_target.draw(text.second);
	}
	for (auto& button : m_vecButtons)
	{
		_target.draw(button.second);
	}
}
