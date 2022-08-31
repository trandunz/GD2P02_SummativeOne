#pragma once
#include "PhysicsBody.h"
class DistanceJoint
{
public:
	DistanceJoint(b2World& _world, b2DistanceJointDef _def);
	~DistanceJoint();

	bool Destroy = false;
private:
	b2DistanceJoint* m_Joint{nullptr};
	b2World* m_World{ nullptr };
};

