// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PulleyJoint.h 
// Description  : PulleyJoint Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "PhysicsBody.h"
class PulleyJoint
{
public:
	PulleyJoint(b2World& _world, b2PulleyJointDef _def);
	/// <summary>
	/// PulleyJoint Destructor
	/// </summary>
	~PulleyJoint();

	bool Destroy{ false };
private:
	b2PulleyJoint* m_Joint{ nullptr };
	b2World* m_World{ nullptr };
};

