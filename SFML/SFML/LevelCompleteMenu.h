#pragma once
#include "Button.h"
class LevelCompleteMenu
{
public:
	LevelCompleteMenu();
	~LevelCompleteMenu();

private:
	void SetStarsBasedOnScore();
	void CreateButtons();
};

