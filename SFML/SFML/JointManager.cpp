// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: JointManager.cpp 
// Description  : JointManager Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "JointManager.h"

void JointManager::SetWorld(b2World& _world)
{
	m_World = &_world;
}

void JointManager::CreateJoint(b2DistanceJointDef _def)
{
	DistanceJoints.emplace_back(new DistanceJoint(*m_World, _def));
}

void JointManager::CreateJoint(b2RevoluteJointDef _def)
{
	RevolutionJoints.emplace_back(new RevolutionJoint(*m_World, _def));
}

void JointManager::CreateJoint(b2PulleyJointDef _def)
{
	PulleyJoints.emplace_back(new PulleyJoint(*m_World, _def));
}

void JointManager::CleanupMarkedJoints()
{
	auto distanceIt = DistanceJoints.begin();
	while (distanceIt != DistanceJoints.end())
	{
		if ((*distanceIt)->Destroy)
		{
			if ((*distanceIt) != nullptr)
			{
				delete * distanceIt;
				*distanceIt = nullptr;
			}
			distanceIt = DistanceJoints.erase(distanceIt);
			continue;
		}
		distanceIt++;
	}

	auto revoIt = RevolutionJoints.begin();
	while (revoIt != RevolutionJoints.end())
	{
		if ((*revoIt)->Destroy)
		{
			if ((*revoIt) != nullptr)
			{
				delete* revoIt;
				*revoIt = nullptr;
			}
			revoIt = RevolutionJoints.erase(revoIt);
			continue;
		}
		revoIt++;
	}

	auto pulleyIt = PulleyJoints.begin();
	while (pulleyIt != PulleyJoints.end())
	{
		if ((*pulleyIt)->Destroy)
		{
			if ((*pulleyIt) != nullptr)
			{
				delete* pulleyIt;
				*pulleyIt = nullptr;
			}
			pulleyIt = PulleyJoints.erase(pulleyIt);
			continue;
		}
		pulleyIt++;
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

	for (auto& joint : RevolutionJoints)
	{
		if (joint)
			delete joint;
		joint = nullptr;
	}
	RevolutionJoints.clear();
	RevolutionJoints.resize(0);

	for (auto& joint : PulleyJoints)
	{
		if (joint)
			delete joint;
		joint = nullptr;
	}
	PulleyJoints.clear();
	PulleyJoints.resize(0);
}

JointManager::JointManager()
{
}

JointManager::~JointManager()
{
	ForceCleanupJoints();
	m_World = nullptr;
}
