#include "ContactListener.h"
#include "Bird.h"
#include "Pig.h"
#include "Destructable.h"
#include "LevelLoader.h"
#include "VFX.h"

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
	float largestImpulse = 0.0f;
	for (auto& impulse : _impulse->normalImpulses)
	{
		if (impulse > 10.0f && impulse > largestImpulse)
		{
			largestImpulse = impulse;
		}
	}

	if (largestImpulse > 10.0f)
	{
		b2WorldManifold worldManifold{};
		_contact->GetWorldManifold(&worldManifold);

		auto& body1UserData = _contact->GetFixtureA()->GetBody()->GetUserData();
		if (body1UserData.pointer)
		{
			UserData* userData = (UserData*)(body1UserData.pointer);
			if (userData->identifier == "Bird")
			{
				Bird* bird = (Bird*)(userData->data);
				LevelLoader::ResetCameraReturnDelay();
			}
			else if (userData->identifier == "Pig")
			{
				Pig* pig = (Pig*)(userData->data);
				pig->TakeDamage(10.0f);
				LevelLoader::ResetCameraReturnDelay();
				*LevelLoader::GetScore() += pig->GetScoreValue();
				VFX::GetInstance().CreateAndPlayTextEffect(
					{
						FloatToString(pig->GetScoreValue(), 0),
						{worldManifold.points[0].x * Statics::Scale, worldManifold.points[0].y * Statics::Scale},
						sf::Color::Green,
						{1.5f,1.5f}
					}, 1.0f);
			}
			else if (userData->identifier == "Destructable")
			{
				Destructable* destructable = (Destructable*)(userData->data);
				destructable->TakeDamage(3.0f);
				LevelLoader::ResetCameraReturnDelay();
				*LevelLoader::GetScore() += destructable->GetScoreValue();
				VFX::GetInstance().CreateAndPlayTextEffect(
					{ 
						FloatToString(destructable->GetScoreValue(), 0),
						{worldManifold.points[0].x * Statics::Scale, worldManifold.points[0].y * Statics::Scale},
						sf::Color::Red
					}, 1.0f);
			}
		}

		auto& body2UserData = _contact->GetFixtureB()->GetBody()->GetUserData();
		if (body2UserData.pointer)
		{
			UserData* userData = (UserData*)(body2UserData.pointer);
			if (userData->identifier == "Bird")
			{
				Bird* bird = (Bird*)(userData->data);
				LevelLoader::ResetCameraReturnDelay();
			}
			else if (userData->identifier == "Pig")
			{
				Pig* pig = (Pig*)(userData->data);
				pig->TakeDamage(10.0f);
				LevelLoader::ResetCameraReturnDelay();
				*LevelLoader::GetScore() += pig->GetScoreValue();
				VFX::GetInstance().CreateAndPlayTextEffect(
					{
						FloatToString(pig->GetScoreValue(), 0),
						{worldManifold.points[0].x * Statics::Scale, worldManifold.points[0].y * Statics::Scale},
						sf::Color::Green,
						{1.5f,1.5f}
					}, 1.0f);
			}
			else if (userData->identifier == "Destructable")
			{
				Destructable* destructable = (Destructable*)(userData->data);
				destructable->TakeDamage(3.0f);
				LevelLoader::ResetCameraReturnDelay();
				*LevelLoader::GetScore() += destructable->GetScoreValue();
				VFX::GetInstance().CreateAndPlayTextEffect(
					{
						FloatToString(destructable->GetScoreValue(), 0),
						{worldManifold.points[0].x * Statics::Scale, worldManifold.points[0].y * Statics::Scale},
						sf::Color::Red
					}, 1.0f);
			}
		}
	}
	
}