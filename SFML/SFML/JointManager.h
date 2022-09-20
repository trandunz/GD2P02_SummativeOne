#pragma once
#include "DistanceJoint.h"
#include "RevolutionJoint.h"

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
	void CreateRevolutionJoint(b2RevoluteJointDef _def);
	void CleanupMarkedJoints();
	void ForceCleanupJoints();

	std::vector<DistanceJoint*> DistanceJoints{};
	std::vector<RevolutionJoint*> RevolutionJoints{};
private:
	JointManager();
	~JointManager();
	JointManager(const JointManager&) = delete;
	JointManager operator = (const JointManager&) = delete;

	b2World* m_World{ nullptr };
};

