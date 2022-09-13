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
	m_ImageEffects[_key].second.setTexture(*_properties.Texture, true);
	m_ImageEffects[_key].second.setScale(_properties.Scale);
	SetOriginCentre(m_ImageEffects[_key].second);
	m_ImageEffects[_key].second.setPosition(_properties.StartPos);
	m_ImageEffects[_key].first = _lifeTime;
}

void VFX::CreateImageEffect(std::string _key, SpecialEffectImageProperties _properties)
{
	m_ImageEffects.insert_or_assign(_key, std::make_pair(float(), sf::Sprite()));
	m_ImageEffects[_key].second.setTexture(*_properties.Texture, true);
	m_ImageEffects[_key].second.setScale(_properties.Scale);
	SetOriginCentre(m_ImageEffects[_key].second);
	m_ImageEffects[_key].second.setPosition(_properties.StartPos);
	m_ImageEffects[_key].second.setColor(_properties.Color);
}

void VFX::CreateAndPlayTextEffect(SpecialEffectTextProperties _properties, float _lifeTime)
{
	int uniqueKey{};
	auto it = m_TextEffects.find(std::to_string(uniqueKey));
	while (it != m_TextEffects.end())
	{
		it = m_TextEffects.find(std::to_string(++uniqueKey));
	}
	m_TextEffects.insert_or_assign(std::to_string(uniqueKey), std::make_pair(float(), sf::Text()));
	m_TextEffects[std::to_string(uniqueKey)].second.setFont(Statics::TimesNewRoman);
	m_TextEffects[std::to_string(uniqueKey)].second.setOutlineThickness(1.0f);
	m_TextEffects[std::to_string(uniqueKey)].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[std::to_string(uniqueKey)].second.setFillColor(_properties.FillColor);
	m_TextEffects[std::to_string(uniqueKey)].second.setString(_properties.Label);
	m_TextEffects[std::to_string(uniqueKey)].second.setScale(_properties.Scale);
	SetOriginCentre(m_TextEffects[std::to_string(uniqueKey)].second);
	m_TextEffects[std::to_string(uniqueKey)].second.setPosition(_properties.StartPos);
	m_TextEffects[std::to_string(uniqueKey)].first = _lifeTime;
}

void VFX::CreateAndPlayTextEffect(std::string _key, SpecialEffectTextProperties _properties, float _lifeTime)
{
	m_TextEffects.insert_or_assign(_key, std::make_pair(float(), sf::Text()));
	m_TextEffects[_key].second.setFont(Statics::TimesNewRoman);
	m_TextEffects[_key].second.setOutlineThickness(1.0f);
	m_TextEffects[_key].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[_key].second.setFillColor(_properties.FillColor);
	m_TextEffects[_key].second.setString(_properties.Label);
	m_TextEffects[_key].second.setScale(_properties.Scale);
	SetOriginCentre(m_TextEffects[_key].second);
	m_TextEffects[_key].second.setPosition(_properties.StartPos);
	m_TextEffects[_key].first = _lifeTime;
}

void VFX::CreateTextEffect(std::string _key, SpecialEffectTextProperties _properties)
{
	m_TextEffects.insert_or_assign(_key, std::make_pair(float(), sf::Text()));
	m_TextEffects[_key].second.setFont(Statics::TimesNewRoman);
	m_TextEffects[_key].second.setOutlineThickness(1.0f);
	m_TextEffects[_key].second.setOutlineColor(_properties.OutlineColor);
	m_TextEffects[_key].second.setFillColor(_properties.FillColor);
	m_TextEffects[_key].second.setString(_properties.Label);
	m_TextEffects[_key].second.setScale(_properties.Scale);
	SetOriginCentre(m_TextEffects[_key].second);
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
