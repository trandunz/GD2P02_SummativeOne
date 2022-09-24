// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Catapult.h 
// Description  : Catapult Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Bird.h"

class Catapult
{
public:
	Catapult(sf::Vector2f _position);
	/// <summary>
	/// Catapult Destructor
	/// </summary>
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

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////
};

