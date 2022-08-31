#include "DistanceJoint.h"

DistanceJoint::DistanceJoint(b2World& _world, b2DistanceJointDef _def)
{
	m_World = &_world;
	m_Joint = (b2DistanceJoint*)m_World->CreateJoint(&_def);
}

DistanceJoint::~DistanceJoint()
{
	if (m_Joint != nullptr)
	{
		m_World->DestroyJoint(m_Joint);
		m_Joint = nullptr;
	}
	m_World = nullptr;
}
