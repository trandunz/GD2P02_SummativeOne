// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: VFX.h 
// Description  : VFX Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

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

	/// <summary>
	/// Force Cleanup all VFX elements
	/// </summary>
	void CleanupElements();
	/// <summary>
	/// Updates all vfx elements
	/// </summary>
	void Update();

	/// <summary>
	/// Creates an image effect with the given key, properties and lifetime and then starts/plays it
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	/// <param name="_lifeTime"></param>
	void CreateAndPlayImageEffect(std::string _key, SpecialEffectImageProperties _properties, float _lifeTime);
	/// <summary>
	/// Creates an image effect with the given key and properties too be used later on
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateImageEffect(std::string _key, SpecialEffectImageProperties _properties);

	/// <summary>
	/// Creates a text effect with a unique key, properties and lifetime and then starts/plays it.
	/// Returns the unique key
	/// </summary>
	/// <param name="_properties"></param>
	/// <param name="_lifeTime"></param>
	/// <returns></returns>
	void CreateAndPlayTextEffect(SpecialEffectTextProperties _properties, float _lifeTime);
	/// <summary>
	/// Creates a text effect with the given key, properties and lifetime and then starts/plays it
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	/// <param name="_lifeTime"></param>
	void CreateAndPlayTextEffect(std::string _key, SpecialEffectTextProperties _properties, float _lifeTime);
	/// <summary>
	/// Creates a text effect with the given key and properties too be used later on
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateTextEffect(std::string _key, SpecialEffectTextProperties _properties);

	/// <summary>
	/// Plays the image effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_lifeTime"></param>
	void PlayImageEffect(std::string _key, float _lifeTime);
	/// <summary>
	/// Plays the text effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_lifeTime"></param>
	void PlayTextEffect(std::string _key, float _lifeTime);
	/// <summary>
	/// stops the image effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	void StopImageEffect(std::string _key);
	/// <summary>
	/// stops the text effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	void StopTextEffect(std::string _key);
	/// <summary>
	/// updates the texture of the image effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_texture"></param>
	void SetImageEffectSprite(std::string _key, sf::Texture& _texture);
	/// <summary>
	/// updates the label / string of the text effect with the specified key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_newLabel"></param>
	void SetTextEffectLabel(std::string _key, std::string _newLabel);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline VFX() {}
	inline VFX(const VFX&) {}
	inline ~VFX() {}

	std::map<std::string, SpecialEffectImage> m_ImageEffects{};
	std::map<std::string, SpecialEffectText> m_TextEffects{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	sf::Sprite& GetImageEffect(std::string _key);
	sf::Text& GetTextEffect(std::string _key);
};

