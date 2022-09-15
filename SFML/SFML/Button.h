#pragma once
#include "Statics.h"

struct ButtonProperties
{
	std::string Label{};
	sf::Vector2f Position{};
	sf::Vector2f Scale = { 1,1 };
	std::function<void()> OnPressLambda{ nullptr };
	sf::Texture* Texture{ nullptr };
};

class Button : public sf::Drawable
{
public:
	Button() {}
	Button(ButtonProperties _properties);
	~Button();

	void CallOnPress();
	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);
	void ResetScale();
	void SetTexture(std::string _fileName);
	void SetTexture(sf::Texture& _texture);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ButtonProperties m_Properties;
	sf::Sprite m_Sprite;
	sf::Text m_Label;
};

