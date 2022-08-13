#pragma once
#include "Helper.h"
#include "Math.h"
#include <functional>
class Button : public sf::Drawable
{
public:
	Button(std::string _label, sf::Vector2f _position, std::function<void()> _onPressLambda, sf::Vector2f _scale = {1,1});
	~Button();

	void CallOnPress();
	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void SetTexture(std::string _fileName);

	std::function<void()> m_OnPressFunction = nullptr;
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::Text m_Label;
};

