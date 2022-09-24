// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: DistanceJoint.h 
// Description  : DistanceJoint Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "PhysicsBody.h"
class DistanceJoint
{
public:
	/// <summary>
	/// Distance Joint Constructor
	/// </summary>
	/// <param name="_world"></param>
	/// <param name="_def"></param>
	DistanceJoint(b2World& _world, b2DistanceJointDef _def);
	/// <summary>
	/// Distance Joint Destructor
	/// </summary>
	~DistanceJoint();

	bool Destroy{ false };
private:
	b2DistanceJoint* m_Joint{nullptr};
	b2World* m_World{ nullptr };
};

