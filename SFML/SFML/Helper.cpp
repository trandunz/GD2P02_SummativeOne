#include "Helper.h"

sf::Int32 Helper::DeltaTime;
sf::Int32 Helper::LastTime;
float Helper::Scale = 30.0f;
sf::RenderWindow Helper::RenderWindow;
sf::Font Helper::TimesNewRoman{};


void Helper::SetOriginCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin({ _sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2 });
}

void Helper::SetOriginCentre(sf::Text& _text)
{
	_text.setOrigin({ _text.getLocalBounds().width / 2, _text.getLocalBounds().height / 1.25f });
}
