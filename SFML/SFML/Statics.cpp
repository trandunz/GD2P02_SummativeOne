#include "Statics.h"

sf::RenderWindow Statics::RenderWindow{};
sf::Event Statics::EventHandle{};

sf::Clock Statics::Time{};
float Statics::DeltaTime{};
float Statics::LastTime{};
float Statics::UnscaledDeltaTime{};
float Statics::TimeScale{1.0f};
bool Statics::IsPaused{false};

float Statics::Scale = 30.0f;

sf::Font Statics::TimesNewRoman{};

void Statics::CalculateDeltaTime()
{
	float currentTime = Time.getElapsedTime().asSeconds();
	UnscaledDeltaTime = currentTime - LastTime;
	DeltaTime = UnscaledDeltaTime * TimeScale;
	LastTime = currentTime;
}

void Statics::TogglePaused()
{
	IsPaused = !IsPaused;

	if (IsPaused)
		TimeScale = 0;
	else
		TimeScale = 1;
}
