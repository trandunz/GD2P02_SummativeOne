#include "ContactListener.h"
#include "Bird.h"
#include "Pig.h"

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

	if (largestImpulse > 5.0f)
	{
		auto& body1UserData = _contact->GetFixtureA()->GetBody()->GetUserData();
		if (body1UserData.pointer)
		{
			UserData* userData = reinterpret_cast<UserData*>(body1UserData.pointer);
			if (userData->identifier == "Bird")
			{
				Bird* bird = reinterpret_cast<Bird*>(userData->data);
				std::cout << "Bird Took " + FloatToString(largestImpulse) + " Force" << std::endl;
			}
			else if (userData->identifier == "Pig")
			{
				Pig* pig = reinterpret_cast<Pig*>(userData->data);
				std::cout << "Pig Took " + FloatToString(largestImpulse) + " Force" << std::endl;
				pig->TakeDamage(10.0f);
			}
		}

		auto& body2UserData = _contact->GetFixtureB()->GetBody()->GetUserData();
		if (body2UserData.pointer)
		{
			UserData* userData = reinterpret_cast<UserData*>(body2UserData.pointer);
			if (userData->identifier == "Bird")
			{
				Bird* bird = reinterpret_cast<Bird*>(userData->data);
				std::cout << "Bird Took " + FloatToString(largestImpulse) + " Force" << std::endl;
			}
			else if (userData->identifier == "Pig")
			{
				Pig* pig = reinterpret_cast<Pig*>(userData->data);
				std::cout << "Pig Took " + FloatToString(largestImpulse) + " Force" << std::endl;
				pig->TakeDamage(10.0f);
			}
		}
	}
	
}