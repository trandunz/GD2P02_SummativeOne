// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: DistanceJoint.cpp 
// Description  : DistanceJoint Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "DistanceJoint.h"

DistanceJoint::DistanceJoint(b2World& _world, b2DistanceJointDef _def)
{
	m_World = &_world;
	m_Joint = (b2DistanceJoint*)m_World->CreateJoint(&_def);
}

DistanceJoint::~DistanceJoint()
{
	// Cleanup this joint
	for (auto joint = m_World->GetJointList(); joint; joint = joint->GetNext())
	{
		if (m_Joint == joint)
		{
			m_World->DestroyJoint(joint);
			joint = nullptr;
			break;
		}
	}
	m_Joint = nullptr;
	m_World = nullptr;
}
