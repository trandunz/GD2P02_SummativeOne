#pragma once
#include "GameLevel.h"

class LevelTwo : public GameLevel
{
public:
	LevelTwo();
	virtual ~LevelTwo();

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;
};