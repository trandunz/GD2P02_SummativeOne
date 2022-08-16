#pragma once
#include "Bird.h"

class Catapult : public sf::Drawable
{
public:
	Catapult(sf::Vector2f _position);
	~Catapult();

	void LoadBird(Bird& _bird);
	void MoveBird();
	void ReleaseBird();

private:
	void SetTexture(std::string _fileName);
	sf::Vector2f GetTrajectoryPoint(float _predictionTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float m_LaunchStrength = 0.2f;

	Bird* m_LoadedBird = nullptr;
	sf::Sprite m_Mesh;
	sf::VertexArray m_TrajectoryLine;

	sf::Vector2f m_FirePosition;
	sf::Vector2f m_FireVector;
};

