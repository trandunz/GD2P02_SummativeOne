// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Catapult.cpp 
// Description  : Catapult Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "Catapult.h"
#include "TextureLoader.h"

Catapult::Catapult(sf::Vector2f _position)
{
	// Seet projectile primitive type
	m_TrajectoryLine.setPrimitiveType(sf::Lines);

	SetTexture(m_BackMesh, "Slingshot_Back.png");
	m_BackMesh.setPosition(_position);
	m_BackMesh.setScale({ 0.12f,0.12f });

	SetTexture(m_FrontMesh, "Slingshot_Front.png");
	m_FrontMesh.setPosition(_position);
	m_FrontMesh.setScale({ 0.12f,0.12f });

	// Set the firing anchor to the top of the slingshot
	m_FirePosition = { m_FrontMesh.getPosition().x, m_FrontMesh.getPosition().y - m_FrontMesh.getGlobalBounds().height/2 };
}

Catapult::~Catapult()
{
	m_LoadedBird = nullptr;
}

void Catapult::LoadBird(Bird& _bird)
{
	m_LoadedBird = &_bird;

	m_LoadedBird->DestroyBody();
	
	// Calculate the firing vector
	 sf::Vector2f mousePos = Statics::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Statics::RenderWindow));
	m_FireVector = mousePos - m_FirePosition;

	// Clamp the firing vector
	if (Mag(m_FireVector) > CATAPULT_DRAW_LENGTH)
	{
		m_FireVector = Normalize(m_FireVector) * CATAPULT_DRAW_LENGTH;
	}
	// Set the birds position
	m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);

	AddPositionsToTrajectoryLine();
}

void Catapult::MoveBird()
{
	m_TrajectoryLine.clear();

	if (m_LoadedBird)
	{
		// Calculate the firing vector
		sf::Vector2f mousePos = Statics::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Statics::RenderWindow));
		m_FireVector = mousePos - m_FirePosition;

		// Clamp the firing vector
		if (Mag(m_FireVector) > CATAPULT_DRAW_LENGTH)
		{
			m_FireVector = Normalize(m_FireVector) * CATAPULT_DRAW_LENGTH;
		}
		// Set the birds position
		m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);

		AddPositionsToTrajectoryLine();
	}
}

void Catapult::ReleaseBird()
{
	m_TrajectoryLine.clear();

	if (m_LoadedBird)
		m_LoadedBird->Launch(m_FireVector * -1.0f * m_LaunchStrength);

	m_LoadedBird = nullptr;
}

void Catapult::DrawFront()
{
	Statics::RenderWindow.draw(m_FrontMesh);
	
}

void Catapult::DrawBack()
{
	Statics::RenderWindow.draw(m_BackMesh);
	Statics::RenderWindow.draw(m_TrajectoryLine);
}

bool Catapult::IsLoaded()
{
	return m_LoadedBird;
}

void Catapult::SetTexture(sf::Sprite& _sprite, std::string _fileName)
{
	_sprite.setTexture(TextureLoader::LoadTexture(_fileName), true);
	SetOriginCentre(_sprite);
}

void Catapult::AddPositionsToTrajectoryLine()
{
	m_TrajectoryLine.clear();
	for (float i = 0; i < 150; i++)
	{
		sf::Vector2f trajectoryPosition = GetTrajectoryPoint(i);
		m_TrajectoryLine.append({ { trajectoryPosition.x, trajectoryPosition.y },sf::Color::Black });
	}
}

sf::Vector2f Catapult::GetTrajectoryPoint(float _predictionTime)
{
	if (m_LoadedBird)
	{
		float timeStep = 1 / 60.0f;
		float predictionTimeSquared = _predictionTime * _predictionTime;
		sf::Vector2f launchVelocity = -m_FireVector * m_LaunchStrength;
		b2Vec2 stepVelocity = timeStep * b2Vec2(launchVelocity.x, launchVelocity.y);
		b2Vec2 stepGravity = timeStep * timeStep * b2Vec2{0,10.0f};
		sf::Vector2f position = m_LoadedBird->GetPosition();
		b2Vec2 prediction = b2Vec2{ position.x / Statics::Scale,   position.y / Statics::Scale } + _predictionTime * stepVelocity + 0.5f * (predictionTimeSquared + _predictionTime) * stepGravity;
		return  { prediction.x * Statics::Scale, prediction.y * Statics::Scale };
	}
	else
	{
		return {};
	}
}
