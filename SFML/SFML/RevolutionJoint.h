#pragma once
#include "PhysicsBody.h"
class RevolutionJoint
{
public:
	RevolutionJoint(b2World& _world, b2RevoluteJointDef _def);
	~RevolutionJoint();

	bool Destroy = false;
private:
	b2RevoluteJoint* m_Joint{ nullptr };
	b2World* m_World{ nullptr };
};

