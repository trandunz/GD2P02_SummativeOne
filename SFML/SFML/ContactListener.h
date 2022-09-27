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
	/// <summary>
	/// Called when two bodies begin colliding
	/// </summary>
	/// <param name="_contact"></param>
	void BeginContact(b2Contact* _contact) override;
	/// <summary>
	/// Called when twwo bodies end colliding
	/// </summary>
	/// <param name="_contact"></param>
	void EndContact(b2Contact* _contact) override;
	/// <summary>
	/// Called just before the collision resolution of two bodies
	/// </summary>
	/// <param name="_contact"></param>
	/// <param name="_oldManifold"></param>
	void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;
	/// <summary>
	/// Called just after the collision resoltion of two bodies
	/// </summary>
	/// <param name="_contact"></param>
	/// <param name="_impulse"></param>
	void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse) override;
};

