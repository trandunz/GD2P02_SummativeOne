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

#define CATAPULT_DRAW_LENGTH 100.0f

class Catapult
{
public:
	/// <summary>
	/// Catapult Constructor
	/// </summary>
	/// <param name="_position"></param>
	Catapult(sf::Vector2f _position);
	/// <summary>
	/// Catapult Destructor
	/// </summary>
	~Catapult();

	/// <summary>
	/// Load the specified bird into the catapult
	/// </summary>
	/// <param name="_bird"></param>
	void LoadBird(Bird& _bird);
	/// <summary>
	/// Move the bird witth a restriction similar to that of a slingshot
	/// </summary>
	void MoveBird();
	/// <summary>
	/// Release the bird with an impulse proportional too the pullback distance
	/// </summary>
	void ReleaseBird();

	/// <summary>
	/// Draw the front part of the catapult
	/// </summary>
	void DrawFront();
	/// <summary>
	/// Draw the back side of the catapult
	/// </summary>
	void DrawBack();

	/// <summary>
	/// Returns the predicted trajectory point and the specified predictiontime
	/// </summary>
	/// <param name="_predictionTime"></param>
	/// <returns></returns>
	sf::Vector2f GetTrajectoryPoint(float _predictionTime);
private:
	/// <summary>
	/// Set the catapults texture too the specified file path
	/// </summary>
	/// <param name="_sprite"></param>
	/// <param name="_fileName"></param>
	void SetTexture(sf::Sprite& _sprite, std::string _fileName);

	/// <summary>
	/// Calculates and adds the trajectory positions too the sf::vertexArray
	/// </summary>
	void AddPositionsToTrajectoryLine();

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

	bool IsLoaded();
};

