#include "ContactListener.h"
#include "Bird.h"

struct UserData
{
	std::string identifier;
	uintptr_t data;
};

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
	bool strongCollision = false;
	for (auto& impule : _impulse->normalImpulses)
	{
		if (impule > 10.0f)
		{
			strongCollision = true;
			break;
		}
	}

	if (strongCollision)
	{
		auto& body1UserData = _contact->GetFixtureA()->GetBody()->GetUserData();
		if (body1UserData.pointer)
		{
			UserData* userData = reinterpret_cast<UserData*>(body1UserData.pointer);
			if (userData->identifier == "Bird")
			{
				Bird* bird = reinterpret_cast<Bird*>(userData->data);
				std::cout << bird->GetPosition().x << std::endl;
			}
		}
	}
	
}