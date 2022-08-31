#include "JointManager.h"

void JointManager::SetWorld(b2World& _world)
{
	m_World = &_world;
}

void JointManager::CreateDistanceJoint(b2DistanceJointDef _def)
{
	DistanceJoints.emplace_back(new DistanceJoint(*m_World, _def));
}

void JointManager::CleanupMarkedJoints()
{
	auto it = DistanceJoints.begin();
	while (it != DistanceJoints.end())
	{
		if ((*it)->Destroy)
		{
			if ((*it) != nullptr)
			{
				delete *it;
				*it = nullptr;
			}
			it = DistanceJoints.erase(it);
			continue;
		}
		it++;
	}
}

void JointManager::ForceCleanupJoints()
{
	for (auto& joint : DistanceJoints)
	{
		if (joint)
			delete joint;
		joint = nullptr;
	}
	DistanceJoints.clear();
	DistanceJoints.resize(0);
}

JointManager::JointManager()
{
}

JointManager::~JointManager()
{
	ForceCleanupJoints();
	m_World = nullptr;
}
