#pragma once

typedef void (*callback_function)(void);

#include "Statics.h"
#include "Math.h"

class Button : public sf::Drawable
{
public:
	Button(std::string _label, sf::Vector2f _position, callback_function _onPressLambda = nullptr, sf::Vector2f _scale = {1,1});
	~Button();

	void CallOnPress();
	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void SetTexture(std::string _fileName);

	callback_function m_OnPressFunction = nullptr;
	sf::Sprite m_Sprite;
	sf::Text m_Label;
};

