#include "LevelThree.h"

LevelThree::LevelThree()
{
	CreateCollisionLess();
	CreateStatics();
	CreateBirds();
	CreatePigs();
	CreateDestructables();
	CreateJoints();
}

LevelThree::~LevelThree()
{
}

void LevelThree::CreateCollisionLess()
{
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 1280 / 2,720 / 2 }));
	m_CollisionLess.back()->SetTexture("Background.jpg");
	m_CollisionLess.back()->SetScale({ 2.65f,2.65f });
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 3 * (1280 / 2) ,720 / 2 }));
	m_CollisionLess.back()->SetTexture("Background.jpg");
	m_CollisionLess.back()->SetScale({ 2.65f,2.65f });
}

void LevelThree::CreateStatics()
{
	m_Statics.emplace_back(new GameObject(*m_World, { -173,680 }));
	m_Statics.emplace_back(new GameObject(*m_World, { 173,680 }));
	for (int i = 0; i < 5; i++)
	{
		m_Statics.emplace_back(new GameObject(*m_World, { 519 + 173.0f * (i * 2),680 }));
	}

	for (auto& object : m_Statics)
	{
		object->SetTexture("Ground.png");
		object->SetBodyType(b2_staticBody);
		object->CreateBody();
	}
}

void LevelThree::CreateBirds()
{
	m_Birds.emplace_back(new Bird(*m_World, { 190,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 150,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 110,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 70,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 30,566 }));

	for (auto& bird : m_Birds)
	{
		bird->SetTexture("Bird.png");
		bird->SetScale({ 0.25f,0.25f });
		bird->SetShapeType(BODYSHAPE::CIRCLE);
		bird->SetBodyType(b2_dynamicBody);
	}
}

void LevelThree::CreatePigs()
{
	m_Pigs.emplace_back(new Pig(*m_World, { 1000,590 }));

	for (auto& pig : m_Pigs)
	{
		pig->SetTexture("Pig.png");
		pig->SetShapeType(BODYSHAPE::CIRCLE);
		pig->SetBodyType(b2_dynamicBody);
		pig->CreateBody();
	}
}

void LevelThree::CreateDestructables()
{
	m_Destructables.emplace_back(new Destructable(*m_World, { 950, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1050, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 390 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 900, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1100, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));
}

void LevelThree::CreateJoints()
{
	//b2DistanceJointDef distanceJoint{};
	//distanceJoint.bodyA = m_Destructables[0]->GetBody();
	//distanceJoint.bodyB = m_Destructables[1]->GetBody();
	//distanceJoint.collideConnected = false;
	//distanceJoint.length = 0.0f;
	//distanceJoint.minLength = 0.0f;
	//distanceJoint.maxLength = 0.0f;
	//
	//JointManager::GetInstance().CreateDistanceJoint(distanceJoint);
}
