#pragma once
#include "GameLevel.h"
class LevelThree :
    public GameLevel
{
public:
	LevelThree();
	virtual ~LevelThree();

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;
};

