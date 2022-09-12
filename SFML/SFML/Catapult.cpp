#include "Catapult.h"
#include "TextureLoader.h"

Catapult::Catapult(sf::Vector2f _position)
{
	m_TrajectoryLine.setPrimitiveType(sf::Lines);

	SetTexture(m_BackMesh, "Slingshot_Back.png");
	m_BackMesh.setPosition(_position);
	m_BackMesh.setScale({ 0.12f,0.12f });
	SetTexture(m_FrontMesh, "Slingshot_Front.png");
	m_FrontMesh.setPosition(_position);
	m_FrontMesh.setScale({ 0.12f,0.12f });
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
	m_FireVector = Statics::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Statics::RenderWindow)) - m_FirePosition;
	
	 sf::Vector2f mousePos = Statics::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Statics::RenderWindow));
	m_FireVector = mousePos - m_FirePosition;

	if (Mag(m_FireVector) > 100.0f)
	{
		m_FireVector = Normalize(m_FireVector) * 100.0f;
	}
	m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);

	m_TrajectoryLine.clear();
	for (float i = 0; i < 240; i++)
	{
		sf::Vector2f trajectoryPosition = GetTrajectoryPoint(i);
		m_TrajectoryLine.append({ { trajectoryPosition.x, trajectoryPosition.y },sf::Color::Black });
	}
}

void Catapult::MoveBird()
{
	m_TrajectoryLine.clear();
	if (m_LoadedBird)
	{
		sf::Vector2f mousePos = Statics::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Statics::RenderWindow));
		m_FireVector = mousePos - m_FirePosition;

		if (Mag(m_FireVector) > 100.0f)
		{
			m_FireVector = Normalize(m_FireVector) * 100.0f;
		}

		m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);

		for (float i = 0; i < 240; i++)
		{
			sf::Vector2f trajectoryPosition = GetTrajectoryPoint(i);
			m_TrajectoryLine.append({ { trajectoryPosition.x, trajectoryPosition.y },sf::Color::Black });
		}
	}
}

void Catapult::ReleaseBird()
{
	m_TrajectoryLine.clear();
	if (m_LoadedBird)
	{
		m_LoadedBird->Launch(m_FireVector * -1.0f * m_LaunchStrength);
	}
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

sf::Vector2f Catapult::GetTrajectoryPoint(float _predictionTime)
{
	if (m_LoadedBird)
	{
		float t = 1 / 60.0f;
		sf::Vector2f launchVelocity = m_FireVector * -1.0f * m_LaunchStrength;
		b2Vec2 stepVelocity = t * b2Vec2(launchVelocity.x, launchVelocity.y);
		b2Vec2 stepGravity = t * t* b2Vec2{0,10.0f};
		sf::Vector2f position = m_LoadedBird->GetPosition();
		b2Vec2 Prediction = b2Vec2{ position.x / Statics::Scale,   position.y / Statics::Scale } + _predictionTime * stepVelocity + 0.5f * (_predictionTime * _predictionTime + _predictionTime) * stepGravity;
		return  { Prediction .x * Statics::Scale, Prediction .y * Statics::Scale };
	}
	return {};
}
