#include "ContactListener.h"
#include "GameObject.h"

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
			GameObject* object = reinterpret_cast<GameObject*>(body1UserData.pointer);
			if (object)
			{
				std::cout << "Collided!" << std::endl;
			}
		}

		auto& body2UserData = _contact->GetFixtureB()->GetBody()->GetUserData();
		if (body2UserData.pointer)
		{
			GameObject* object = reinterpret_cast<GameObject*>(body1UserData.pointer);
			if (object)
			{
				std::cout << "Collided!" << std::endl;
			}
		}
	}
	
}