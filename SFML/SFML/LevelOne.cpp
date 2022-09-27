// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: LevelOne.cpp 
// Description  : LevelOne Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "LevelOne.h"
#include "JointManager.h"
#include "Utility.h"
#include "Pig.h"
#include "Destructable.h"

LevelOne::LevelOne()
	: GameLevel()
{
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
	CreateJoints();
}

LevelOne::~LevelOne()
{
}

void LevelOne::CreateBirds()
{
	m_Birds.emplace_back(new Bird(*m_World, { 190,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 150,566 }, Bird::TYPE::DASH));
	m_Birds.emplace_back(new Bird(*m_World, { 110,566 }, Bird::TYPE::DIVEBOMB));
	m_Birds.emplace_back(new Bird(*m_World, { 70,566 }, Bird::TYPE::DASH));
	m_Birds.emplace_back(new Bird(*m_World, { 30,566 }, Bird::TYPE::EXPLOSIVE));
}

void LevelOne::CreatePigs()
{
	m_Pigs.emplace_back(new Pig(*m_World, { 1000,590 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1060,350 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 940,350 }));
}

void LevelOne::CreateDestructables()
{
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 250 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 150 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 930, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1070, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 390 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::STONE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::STONE));

	m_Destructables.emplace_back(new Destructable(*m_World, { 880, 520 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(-90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1120, 520 }, Destructable::SHAPE::CORNER, Destructable::TYPE::WOOD));
}

void LevelOne::CreateJoints()
{
	b2RevoluteJointDef revolutionJoint{};
	revolutionJoint.Initialize(m_Destructables[0]->GetBody(), m_Destructables[1]->GetBody(), m_Destructables[1]->GetBody()->GetWorldCenter());
	revolutionJoint.collideConnected = false;
	revolutionJoint.enableMotor = true;
	revolutionJoint.motorSpeed = 1000.0f;
	revolutionJoint.maxMotorTorque = 10.0f;
	JointManager::GetInstance().CreateJoint(revolutionJoint);
}
