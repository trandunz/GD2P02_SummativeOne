#include "Helper.h"

sf::Int32 Helper::DeltaTime;
sf::Int32 Helper::LastTime;
float Helper::Scale = 30.0f;
sf::RenderWindow Helper::RenderWindow;


void Helper::SetOriginCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin({ _sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2 });
}
