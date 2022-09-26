// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: GUI.h 
// Description  : GUI Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Button.h"

struct TextProperties
{
	sf::Vector2f StartPos{};
	std::string String{};
	sf::Color FillColor{ sf::Color::White };
	sf::Color OutlineColor{ sf::Color::Black };
	int iCharacterSize{ 36 };
};

struct ImageProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	float Rotation{};
};

class GUI : public sf::Drawable
{
public:
	inline static GUI& GetInstance()
	{
		static GUI instance;
		return instance;
	}

	/// <summary>
	/// Force Cleanup all GUI elements
	/// </summary>
	void CleanupElements();

	/// <summary>
	/// Handles all GUI events such as clicking a button
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// Updates all GUI elements
	/// </summary>
	void Update();

	/// <summary>
	/// Creates a text element with the specified key and properties
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateText(std::string _key, TextProperties _properties);
	/// <summary>
	/// Returns a text element with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <returns></returns>
	sf::Text& GetText(std::string _key);
	/// <summary>
	/// Sets the text label on the text element specified by the given key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_value"></param>
	void SetText(std::string _key, std::string _value);
	/// <summary>
	/// Appeends the text label on the text element specified by the given key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_value"></param>
	void AppendText(std::string _key, std::string _value);

	/// <summary>
	/// Creates an image element with the specified key and properties
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateImage(std::string _key, ImageProperties _properties);
	/// <summary>
	/// Returns an image element with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <returns></returns>
	sf::Sprite& GetImage(std::string _key);
	/// <summary>
	/// Sets the sprite for an image element witth the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_texture"></param>
	void SetImageSprite(std::string _key, sf::Texture& _texture);

	/// <summary>
	/// Creates a button element with the specified key and properties
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateButton(std::string _key, ButtonProperties _properties);
	/// <summary>
	/// Returns a button element with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <returns></returns>
	Button* GetButton(std::string _key);
	/// <summary>
	/// Resets the scale of all buttons too there original scale specified on button creation
	/// </summary>
	void ResetAllButtonsScale();

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline GUI() {}
	inline GUI(const GUI&) {}
	inline ~GUI() {}

	sf::View m_UIView{};
	std::map<std::string, sf::Sprite> m_vecImages{};
	std::map<std::string, sf::Text> m_vecTexts{};
	std::map<std::string, Button> m_vecButtons{};
};

