#include "Catapult.h"
#include "TextureLoader.h"

Catapult::Catapult(sf::Vector2f _position)
{
	m_TrajectoryLine.setPrimitiveType(sf::Lines);

	SetTexture("Slingshot.png");
	m_Mesh.setPosition(_position);
	m_Mesh.setScale({ 0.12f,0.12f });
	m_FirePosition = { m_Mesh.getPosition().x, m_Mesh.getPosition().y - m_Mesh.getGlobalBounds().height/2 };
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

void Catapult::SetTexture(std::string _fileName)
{
	m_Mesh.setTexture(TextureLoader::LoadTexture(_fileName), true);
	SetOriginCentre(m_Mesh);
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

void Catapult::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Mesh);
	target.draw(m_TrajectoryLine);
}
