// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Statics.cpp 
// Description  : Statics Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

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

/// <summary>
/// Calculates both Unscaled deltatime and normal deltaTime
/// </summary>
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
