// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PulleyJoint.cpp 
// Description  : PulleyJoint Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "PulleyJoint.h"

PulleyJoint::PulleyJoint(b2World& _world, b2PulleyJointDef _def)
{
	m_World = &_world;
	m_Joint = (b2PulleyJoint*)m_World->CreateJoint(&_def);
}

PulleyJoint::~PulleyJoint()
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
