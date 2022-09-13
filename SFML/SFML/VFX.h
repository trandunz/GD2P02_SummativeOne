#pragma once
#include "Statics.h"

using SpecialEffectImage = std::pair<float, sf::Sprite>;
using SpecialEffectText = std::pair<float, sf::Text>;

struct SpecialEffectImageProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	sf::Color Color{ 1,1,1 };
};

struct SpecialEffectTextProperties
{
	sf::String Label{};
	sf::Vector2f StartPos{};
	sf::Color FillColor{ 255,255,255 };
	sf::Vector2f Scale{ 1,1 };
	sf::Color OutlineColor{ 0,0,0 };
};

class VFX : public sf::Drawable
{
public:
	inline static VFX& GetInstance()
	{
		static VFX instance;
		return instance;
	}

	void CleanupElements();
	void Update();

	void CreateAndPlayImageEffect(std::string _key, SpecialEffectImageProperties _properties, float _lifeTime);
	void CreateImageEffect(std::string _key, SpecialEffectImageProperties _properties);

	void CreateAndPlayTextEffect(SpecialEffectTextProperties _properties, float _lifeTime);
	void CreateAndPlayTextEffect(std::string _key, SpecialEffectTextProperties _properties, float _lifeTime);
	void CreateTextEffect(std::string _key, SpecialEffectTextProperties _properties);

	sf::Sprite& GetImageEffect(std::string _key);
	sf::Text& GetTextEffect(std::string _key);

	void PlayImageEffect(std::string _key, float _lifeTime);
	void PlayTextEffect(std::string _key, float _lifeTime);
	void StopImageEffect(std::string _key);
	void StopTextEffect(std::string _key);
	void SetImageEffectSprite(std::string _key, sf::Texture& _texture);
	void SetTextEffectLabel(std::string _key, std::string _newLabel);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline VFX() {}
	inline VFX(const VFX&) {}
	inline ~VFX() {}

	std::map<std::string, SpecialEffectImage> m_ImageEffects{};
	std::map<std::string, SpecialEffectText> m_TextEffects{};
};

