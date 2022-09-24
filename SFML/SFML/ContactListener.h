// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: ContactListener.h 
// Description  : ContactListener Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include <box2d/box2d.h>

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* _contact) override;

	void EndContact(b2Contact* _contact) override;

	void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;

	void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse) override;
};

