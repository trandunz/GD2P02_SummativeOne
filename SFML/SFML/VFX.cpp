// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: VFX.cpp 
// Description  : VFX Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "VFX.h"
#include "Math.h"
#include "Utility.h"

void VFX::CleanupElements()
{
	CleanupMap(m_ImageEffects);
	CleanupMap(m_TextEffects);
}

void VFX::Update()
{
	for (auto& effect : m_ImageEffects)
	{
		if (effect.second.first > 0)
		{
			effect.second.first -= Statics::DeltaTime;
		}
	}

	for (auto& effect : m_TextEffects)
	{
		if (effect.second.first > 0)
		{
			effect.second.first -= Statics::DeltaTime;
		}
	}
}

void VFX::CreateAndPlayImageEffect(std::string _key, SpecialEffectImageProperties _properties, float _lifeTime)
{
	m_ImageEffects.insert_or_assign(_key, std::make_pair(float(), sf::Sprite()));

	// Set the lifetime
	m_ImageEffects[_key].first = _lifeTime;

	m_ImageEffects[_key].second.setTexture(*_properties.Texture, true);

	SetOriginCentre(m_ImageEffects[_key].second);

	m_ImageEffects[_key].second.setScale(_properties.Scale);
	m_ImageEffects[_key].second.setPosition(_properties.StartPos);

}

void VFX::CreateImageEffect(std::string _key, SpecialEffectImageProperties _properties)
{
	m_ImageEffects.insert_or_assign(_key, std::make_pair(float(), sf::Sprite()));

	m_ImageEffects[_key].second.setTexture(*_properties.Texture, true);

	SetOriginCentre(m_ImageEffects[_key].second);

	m_ImageEffects[_key].second.setScale(_properties.Scale);
	m_ImageEffects[_key].second.setPosition(_properties.StartPos);

	m_ImageEffects[_key].second.setColor(_properties.Color);
}

void VFX::CreateAndPlayTextEffect(SpecialEffectTextProperties _properties, float _lifeTime)
{
	// Loop through and get a unique map key
	int uniqueKey{};
	auto it = m_TextEffects.find(std::to_string(uniqueKey));
	while (it != m_TextEffects.end())
	{
		it = m_TextEffects.find(std::to_string(++uniqueKey));
	}

	m_TextEffects.insert_or_assign(std::to_string(uniqueKey), std::make_pair(float(), sf::Text()));

	// Set lifetime
	m_TextEffects[std::to_string(uniqueKey)].first = _lifeTime;

	m_TextEffects[std::to_string(uniqueKey)].second.setFont(Statics::TimesNewRoman);

	// Set outline and colour
	m_TextEffects[std::to_string(uniqueKey)].second.setOutlineThickness(1.0f);
	m_TextEffects[std::to_string(uniqueKey)].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[std::to_string(uniqueKey)].second.setFillColor(_properties.FillColor);

	m_TextEffects[std::to_string(uniqueKey)].second.setString(_properties.Label);

	SetOriginCentre(m_TextEffects[std::to_string(uniqueKey)].second);
	m_TextEffects[std::to_string(uniqueKey)].second.setScale(_properties.Scale);
	m_TextEffects[std::to_string(uniqueKey)].second.setPosition(_properties.StartPos);
}

void VFX::CreateAndPlayTextEffect(std::string _key, SpecialEffectTextProperties _properties, float _lifeTime)
{
	m_TextEffects.insert_or_assign(_key, std::make_pair(float(), sf::Text()));
	
	// Set lifetime
	m_TextEffects[_key].first = _lifeTime;

	m_TextEffects[_key].second.setFont(Statics::TimesNewRoman);

	// Set outline and colour
	m_TextEffects[_key].second.setOutlineThickness(1.0f);
	m_TextEffects[_key].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[_key].second.setFillColor(_properties.FillColor);

	m_TextEffects[_key].second.setString(_properties.Label);

	SetOriginCentre(m_TextEffects[_key].second);
	m_TextEffects[_key].second.setScale(_properties.Scale);
	m_TextEffects[_key].second.setPosition(_properties.StartPos);
}

void VFX::CreateTextEffect(std::string _key, SpecialEffectTextProperties _properties)
{
	m_TextEffects.insert_or_assign(_key, std::make_pair(float(), sf::Text()));

	m_TextEffects[_key].second.setFont(Statics::TimesNewRoman);

	// Set outline and colour
	m_TextEffects[_key].second.setOutlineThickness(1.0f);
	m_TextEffects[_key].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[_key].second.setFillColor(_properties.FillColor);

	m_TextEffects[_key].second.setString(_properties.Label);

	SetOriginCentre(m_TextEffects[_key].second);
	m_TextEffects[_key].second.setScale(_properties.Scale);
	m_TextEffects[_key].second.setPosition(_properties.StartPos);
}

sf::Sprite& VFX::GetImageEffect(std::string _key)
{
	return m_ImageEffects[_key].second;
}

sf::Text& VFX::GetTextEffect(std::string _key)
{
	return m_TextEffects[_key].second;
}

void VFX::PlayImageEffect(std::string _key, float _lifeTime)
{
	m_ImageEffects[_key].first = _lifeTime;
}

void VFX::PlayTextEffect(std::string _key, float _lifeTime)
{
	m_TextEffects[_key].first = _lifeTime;
}

void VFX::StopImageEffect(std::string _key)
{
	m_ImageEffects[_key].first = 0.0f;
}

void VFX::StopTextEffect(std::string _key)
{
	m_TextEffects[_key].first = 0.0f;
}

void VFX::SetImageEffectSprite(std::string _key, sf::Texture& _texture)
{
	m_ImageEffects[_key].second.setTexture(_texture, true);

	// Reset origin
	SetOriginCentre(m_ImageEffects[_key].second);
}

void VFX::SetTextEffectLabel(std::string _key, std::string _newLabel)
{
	m_TextEffects[_key].second.setString(_newLabel);
}

void VFX::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& effect : m_ImageEffects)
	{
		if (effect.second.first > 0)
			_target.draw(effect.second.second);
	}
	for (auto& effect : m_TextEffects)
	{
		if (effect.second.first > 0)
			_target.draw(effect.second.second);
	}
}
