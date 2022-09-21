#pragma once
#include "PhysicsBody.h"
class PulleyJoint
{
public:
	PulleyJoint(b2World& _world, b2PulleyJointDef _def);
	~PulleyJoint();

	bool Destroy = false;
private:
	b2PulleyJoint* m_Joint{ nullptr };
	b2World* m_World{ nullptr };
};

