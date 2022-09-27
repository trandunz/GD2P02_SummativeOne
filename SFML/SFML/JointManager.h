// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: JointManager.h 
// Description  : JointManager Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "DistanceJoint.h"
#include "RevolutionJoint.h"
#include "PulleyJoint.h"

class JointManager
{
public:
	static JointManager& GetInstance()
	{
		static JointManager instance;
		return instance;
	}

	/// <summary>
	/// Create a distance joint with the specified definition
	/// </summary>
	/// <param name="_def"></param>
	void CreateJoint(b2DistanceJointDef _def);
	/// <summary>
	/// Create a revolution joint with the specified definition
	/// </summary>
	/// <param name="_def"></param>
	void CreateJoint(b2RevoluteJointDef _def);
	/// <summary>
	/// Create a Pulley joint with the specified definition
	/// </summary>
	/// <param name="_def"></param>
	void CreateJoint(b2PulleyJointDef _def);

	/// <summary>
	/// Cleanup any joints marked for cleanup
	/// </summary>
	void CleanupMarkedJoints();
	/// <summary>
	/// Force cleans up all joints
	/// </summary>
	void ForceCleanupJoints();

	std::vector<DistanceJoint*> DistanceJoints{};
	std::vector<RevolutionJoint*> RevolutionJoints{};
	std::vector<PulleyJoint*> PulleyJoints{};
private:
	JointManager();
	/// <summary>
	/// JointManager Destructor
	/// </summary>	
	~JointManager();
	JointManager(const JointManager&) = delete;
	JointManager operator = (const JointManager&) = delete;

	b2World* m_World{ nullptr };

public:
	///////////////////////
	// Getters & Setters //
	///////////////////////

	void SetWorld(b2World& _world);
};

