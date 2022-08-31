#pragma once
#include "DistanceJoint.h"

class JointManager
{
public:
	static JointManager& GetInstance()
	{
		static JointManager instance;
		return instance;
	}

	void SetWorld(b2World& _world);
	void CreateDistanceJoint(b2DistanceJointDef _def);
	void CleanupMarkedJoints();
	void ForceCleanupJoints();

	std::vector<DistanceJoint*> DistanceJoints{};
private:
	JointManager();
	~JointManager();
	JointManager(const JointManager&) = delete;
	JointManager operator = (const JointManager&) = delete;

	b2World* m_World{ nullptr };
};

