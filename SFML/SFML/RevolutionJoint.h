// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: RevolutionJoint.h 
// Description  : RevolutionJoint Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "PhysicsBody.h"
class RevolutionJoint
{
public:
	RevolutionJoint(b2World& _world, b2RevoluteJointDef _def);
	/// <summary>
	/// RevolutionJoint Destructor
	/// </summary>
	~RevolutionJoint();

	bool Destroy = false;
private:
	b2RevoluteJoint* m_Joint{ nullptr };
	b2World* m_World{ nullptr };
};

