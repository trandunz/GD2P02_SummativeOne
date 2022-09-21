#include "PulleyJoint.h"

PulleyJoint::PulleyJoint(b2World& _world, b2PulleyJointDef _def)
{
	m_World = &_world;
	m_Joint = (b2PulleyJoint*)m_World->CreateJoint(&_def);
}

PulleyJoint::~PulleyJoint()
{
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
