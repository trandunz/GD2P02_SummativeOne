#include "RevolutionJoint.h"

RevolutionJoint::RevolutionJoint(b2World& _world, b2RevoluteJointDef _def)
{
	m_World = &_world;
	m_Joint = (b2RevoluteJoint*)m_World->CreateJoint(&_def);
}

RevolutionJoint::~RevolutionJoint()
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

