// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: ContactListener.cpp 
// Description  : ContactListener Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "ContactListener.h"
#include "Bird.h"
#include "Pig.h"
#include "Destructable.h"
#include "LevelLoader.h"
#include "VFX.h"

#define IMPULSE_THRESHHOLD 10.0f

void ContactListener::BeginContact(b2Contact* _contact)
{

}

void ContactListener::EndContact(b2Contact* _contact)
{

}

void ContactListener::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{

}

void ContactListener::PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse)
{
	// Get the largest impulse of the two
	float largestImpulse{};
	for (auto& impulse : _impulse->normalImpulses)
	{
		if (impulse > IMPULSE_THRESHHOLD && impulse > largestImpulse)
		{
			largestImpulse = impulse;
		}
	}

	if (largestImpulse > IMPULSE_THRESHHOLD)
	{
		// Get world manifold / Contact positions
		b2WorldManifold worldManifold{};
		_contact->GetWorldManifold(&worldManifold);

		// Get body 1 user data
		auto& body1UserData = _contact->GetFixtureA()->GetBody()->GetUserData();
		if (body1UserData.pointer)
		{
			// Cast to userData
			UserData* userData = (UserData*)(body1UserData.pointer);
			// If bird took damage
			if (userData->identifier == "Bird")
			{
				Bird* bird = (Bird*)(userData->data);
				LevelLoader::ResetCameraReturnDelay();
			}
			// If pig took damage
			else if (userData->identifier == "Pig")
			{
				Pig* pig = (Pig*)(userData->data);
				pig->TakeDamage(10.0f, worldManifold.points[0]);
				LevelLoader::ResetCameraReturnDelay();
			}
			// If destructable took damage
			else if (userData->identifier == "Destructable")
			{
				Destructable* destructable = (Destructable*)(userData->data);
				destructable->TakeDamage(3.0f, worldManifold.points[0]);
				LevelLoader::ResetCameraReturnDelay();
			}
		}

		// Get body 2 user data
		auto& body2UserData = _contact->GetFixtureB()->GetBody()->GetUserData();
		if (body2UserData.pointer)
		{
			// Cast to userData
			UserData* userData = (UserData*)(body2UserData.pointer);
			// If bird took damage
			if (userData->identifier == "Bird")
			{
				Bird* bird = (Bird*)(userData->data);
				LevelLoader::ResetCameraReturnDelay();
			}
			// If pig took damage
			else if (userData->identifier == "Pig")
			{
				Pig* pig = (Pig*)(userData->data);
				pig->TakeDamage(10.0f, worldManifold.points[0]);
				LevelLoader::ResetCameraReturnDelay();
			}
			// If destructable took damage
			else if (userData->identifier == "Destructable")
			{
				Destructable* destructable = (Destructable*)(userData->data);
				destructable->TakeDamage(3.0f, worldManifold.points[0]);
				LevelLoader::ResetCameraReturnDelay();
			}
		}
	}
	
}