#include "LevelOne.h"
#include "JointManager.h"

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

void LevelOne::CreateCollisionLess()
{
	sf::Vector2f windowCenter = Statics::RenderWindow.getView().getCenter();
	windowCenter.y -= 720 / 6;
	m_CollisionLess.emplace_back(new GameObject(*m_World, windowCenter));
	m_CollisionLess.back()->SetTexture("Background.png");
	m_CollisionLess.emplace_back(new GameObject(*m_World, { windowCenter.x * 3, windowCenter.y }));
	m_CollisionLess.back()->SetTexture("Background.png");

	m_CollisionLess.emplace_back(new GameObject(*m_World, { -173,550 }));
	m_CollisionLess.back()->SetTexture("Grass.png");
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 173,550 }));
	m_CollisionLess.back()->SetTexture("Grass.png");
	for (int i = 0; i < 5; i++)
	{
		m_CollisionLess.emplace_back(new GameObject(*m_World, { 519 + 173.0f * (i * 2),550 }));
		m_CollisionLess.back()->SetTexture("Grass.png");
	}
}

void LevelOne::CreateStatics()
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
	JointManager::GetInstance().CreateRevolutionJoint(revolutionJoint);
}
