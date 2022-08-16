#include "Statics.h"

sf::RenderWindow Statics::RenderWindow{};
sf::Event Statics::EventHandler{};

sf::Clock Statics::Time{};
float Statics::DeltaTime{};
float Statics::LastTime{};
float Statics::UnscaledDeltaTime{};
float Statics::TimeScale{};

float Statics::Scale = 30.0f;

sf::Font Statics::TimesNewRoman{};

void Statics::CalculateDeltaTime()
{
	float currentTime = Time.getElapsedTime().asSeconds();
	UnscaledDeltaTime = currentTime - LastTime;
	DeltaTime = UnscaledDeltaTime * TimeScale;
	LastTime = currentTime;
}
