// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelTwo.cpp 
// Description  : LevelTwo Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "LevelTwo.h"
#include "JointManager.h"
#include "Utility.h"
#include "Pig.h"
#include "Destructable.h"

LevelTwo::LevelTwo()
{
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
	CreateJoints();
}

LevelTwo::~LevelTwo()
{
}

void LevelTwo::CreateBirds()
{
	m_Birds.emplace_back(new Bird(*m_World, { 190,566 }, Bird::TYPE::DIVEBOMB));
	m_Birds.emplace_back(new Bird(*m_World, { 150,566 }, Bird::TYPE::DIVEBOMB));
	m_Birds.emplace_back(new Bird(*m_World, { 110,566 }, Bird::TYPE::DASH));
	m_Birds.emplace_back(new Bird(*m_World, { 70,566 }, Bird::TYPE::DIVEBOMB));
	m_Birds.emplace_back(new Bird(*m_World, { 30,566 }, Bird::TYPE::EXPLOSIVE));
}

void LevelTwo::CreatePigs()
{
	m_Pigs.emplace_back(new Pig(*m_World, { 1120,170 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1038, 500 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1198,500 }));
}

void LevelTwo::CreateDestructables()
{
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 190 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1220, 190 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1010, 190 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(-90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 320 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 260 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 800, 500 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 800, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 960, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 500 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));

	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 360 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 380 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 380 }, Destructable::SHAPE::CORNER, Destructable::TYPE::STONE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 380 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(180.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 960, 500 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 960, 500 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(180.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 960, 380 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 1040, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1040, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.back()->SetRotation(180.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.back()->SetRotation(180.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1198, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1198, 550 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.back()->SetRotation(180.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 1278, 500 }, Destructable::SHAPE::CORNER, Destructable::TYPE::ICE));
	m_Destructables.back()->SetRotation(-90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1278, 500 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 1038, 500 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1118, 500 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1198, 500 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 1358, 380 }, Destructable::SHAPE::CORNER, Destructable::TYPE::STONE));
	m_Destructables.back()->SetRotation(-90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1358, 380 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1278, 380 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 1278, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1358, 500 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1358, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1428, 550 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1428, 500 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::DIAMOND));
}

void LevelTwo::CreateJoints()
{
	b2DistanceJointDef distanceJoint{};

	distanceJoint.bodyA = m_Destructables[0]->GetBody();
	distanceJoint.bodyB = m_Destructables[1]->GetBody();
	distanceJoint.collideConnected = false;
	distanceJoint.length = 0.1f;
	distanceJoint.minLength = 0.0f;
	distanceJoint.maxLength = 0.1f;
	distanceJoint.localAnchorA = { 2,2 };
	JointManager::GetInstance().CreateJoint(distanceJoint);

	distanceJoint.bodyA = m_Destructables[0]->GetBody();
	distanceJoint.bodyB = m_Destructables[2]->GetBody();
	distanceJoint.collideConnected = false;
	distanceJoint.length = 0.1f;
	distanceJoint.minLength = 0.0f;
	distanceJoint.maxLength = 0.1f;
	distanceJoint.localAnchorA = { -2,2 };
	JointManager::GetInstance().CreateJoint(distanceJoint);

	distanceJoint.bodyA = m_Destructables[0]->GetBody();
	distanceJoint.bodyB = m_Pigs[0]->GetBody();
	distanceJoint.collideConnected = false;
	distanceJoint.length = 0.1f;
	distanceJoint.minLength = 0.0f;
	distanceJoint.maxLength = 0.1f;
	distanceJoint.localAnchorA = { 0,-1.8f };
	JointManager::GetInstance().CreateJoint(distanceJoint);
}
