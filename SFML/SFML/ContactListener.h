#pragma once
#include <box2d/box2d.h>
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* _contact) override;

	void EndContact(b2Contact* _contact) override;

	void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;

	void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse) override;
};

