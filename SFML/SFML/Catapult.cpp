#include "Catapult.h"

Catapult::Catapult(sf::Vector2f _position)
{
	SetTexture("Catapult.png");
	m_Mesh.setPosition(_position);
	m_Mesh.setScale({ 1.5f,1.5f });
	m_FirePosition = { m_Mesh.getPosition().x, m_Mesh.getPosition().y - m_Mesh.getLocalBounds().height/2 };
}

Catapult::~Catapult()
{
	m_LoadedBird = nullptr;
}

void Catapult::LoadBird(GameObject& _bird)
{
	m_LoadedBird = &_bird;
	m_LoadedBird->DeleteBody();
	m_FireVector = Helper::RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(Helper::RenderWindow)) - m_FirePosition;
	m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);
}

void Catapult::MoveBird()
{
	if (m_LoadedBird)
	{
		sf::Vector2f mousePos = {(float) sf::Mouse::getPosition(Helper::RenderWindow).x, (float)sf::Mouse::getPosition(Helper::RenderWindow).y };
		m_FireVector = mousePos - m_FirePosition;

		if (Mag(m_FireVector) > 100.0f)
		{
			m_FireVector = Normalize(m_FireVector) * 100.0f;
		}

		m_LoadedBird->SetPosition(m_FirePosition + m_FireVector);
	}
}

void Catapult::ReleaseBird()
{
	if (m_LoadedBird)
	{
		m_LoadedBird->Launch(m_FireVector * -1.0f * m_LaunchStrength);
	}
	m_LoadedBird = nullptr;
}

void Catapult::SetTexture(std::string _fileName)
{
	m_Texture.loadFromFile("Resources/Sprites/" + _fileName);
	m_Mesh.setTexture(m_Texture, true);
	Helper::SetOriginCentre(m_Mesh);
}

void Catapult::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Mesh);
}
