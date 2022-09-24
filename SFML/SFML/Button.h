// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Button.h 
// Description  : Button Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

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
	/// <summary>
	/// Button Destructor
	/// </summary>
	~Button();

	void CallOnPress();
	void ResetScale();


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ButtonProperties m_Properties;
	sf::Sprite m_Sprite;
	sf::Text m_Label;

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	void SetTexture(std::string _fileName);
	void SetTexture(sf::Texture& _texture);

	void SetLabel(std::string _newLabel);

	void SetPosition(sf::Vector2f _position);

	void SetScale(sf::Vector2f _scale);
};

