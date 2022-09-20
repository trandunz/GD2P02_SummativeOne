#pragma once
#include "Button.h"

struct TextProperties
{
	sf::Vector2f StartPos{};
	std::string String{};
	sf::Color FillColor{};
	sf::Color OutlineColor{};
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

	void CleanupImageElement(std::string _key);
	void CleanupButtonElement(std::string _key);
	void CleanupTextElement(std::string _key);
	void CleanupElements();
	void PollEvents();
	void Update();

	void CreateText(std::string _key, TextProperties _properties);
	sf::Text& GetText(std::string _key);
	void SetText(std::string _key, std::string _value);
	void AppendText(std::string _key, std::string _value);

	void CreateImage(std::string _key, ImageProperties _properties);
	sf::Sprite& GetImage(std::string _key);
	void SetImageSprite(std::string _key, sf::Texture& _texture);

	void CreateButton(std::string _key, ButtonProperties _properties);
	Button* GetButton(std::string _key);
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

