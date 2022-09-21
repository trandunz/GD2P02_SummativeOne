#pragma once
#include "GameLevel.h"
class LevelThree :
    public GameLevel
{
public:
	LevelThree();
	virtual ~LevelThree();

	void Update() override;
	void Draw() override;

protected:
	void CreateCollisionLess() override;
	void CreateStatics() override;
	void CreateBirds() override;
	void CreatePigs() override;
	void CreateDestructables() override;
	void CreateJoints() override;

	void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector) override;

private:
	sf::VertexArray m_PulleyJointRope{ sf::LinesStrip };
	Destructable* m_PulleyBlockA{ nullptr };
	Destructable* m_PulleyBlockB{ nullptr };
};

