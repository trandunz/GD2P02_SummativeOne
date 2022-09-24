// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Level.h 
// Description  : Level Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once

class Level
{
public:
	Level() {}
	/// <summary>
	/// Level Destructor
	/// </summary>	
	virtual ~Level() {}

	virtual void PollEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

