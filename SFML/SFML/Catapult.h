#pragma once
#include "Bird.h"

class Catapult
{
public:
	Catapult(sf::Vector2f _position);
	~Catapult();

	void LoadBird(Bird& _bird);
	void MoveBird();
	void ReleaseBird();

	void DrawFront();
	void DrawBack();

	bool IsLoaded();
	sf::Vector2f GetTrajectoryPoint(float _predictionTime);
private:
	void SetTexture(sf::Sprite& _sprite, std::string _fileName);

	float m_LaunchStrength = 0.2f;

	Bird* m_LoadedBird = nullptr;
	sf::Sprite m_FrontMesh;
	sf::Sprite m_BackMesh;
	sf::VertexArray m_TrajectoryLine;

	sf::Vector2f m_FirePosition;
	sf::Vector2f m_FireVector;
};

