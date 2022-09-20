#pragma once
#include "GameLevel.h"

class LevelOne : public GameLevel
{
public:
	LevelOne();
	virtual ~LevelOne();

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;
};