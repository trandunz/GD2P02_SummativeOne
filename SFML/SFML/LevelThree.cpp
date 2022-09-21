#include "LevelThree.h"
#include "JointManager.h"
#include "GUI.h"
#include "VFX.h"
#include "PauseMenu.h"
#include "LevelCompleteMenu.h"

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
	if (m_PulleyBlockA)
		delete m_PulleyBlockA;
	m_PulleyBlockA = nullptr;

	if (m_PulleyBlockB)
		delete m_PulleyBlockB;
	m_PulleyBlockB = nullptr;
}

void LevelThree::Update()
{
	GameLevel::Update();
	if (m_PulleyBlockA)
	{
		m_PulleyBlockA->Update();
	}
	if (m_PulleyBlockB)
	{
		m_PulleyBlockB->Update();
	}
}

void LevelThree::Draw()
{
	m_PulleyJointRope.clear();

	if (m_PulleyBlockA && m_PulleyBlockB)
	{
		m_PulleyJointRope.append({ m_PulleyBlockA->GetPosition(),sf::Color::Black });
		m_PulleyJointRope.append({ m_Statics[7]->GetPosition(),sf::Color::Black });
		m_PulleyJointRope.append({ m_Statics[8]->GetPosition(),sf::Color::Black });
		m_PulleyJointRope.append({ m_PulleyBlockB->GetPosition(),sf::Color::Black });
	}

	//
	// Draw
	//
	Statics::RenderWindow.setView(m_View);

	for (auto& object : m_CollisionLess)
	{
		Statics::RenderWindow.draw(*object);
	}

	Statics::RenderWindow.draw(m_PulleyJointRope);

	for (auto& object : m_Statics)
	{
		Statics::RenderWindow.draw(*object);
	}

	m_Catapult.DrawBack();
	for (auto& object : m_Destructables)
	{
		Statics::RenderWindow.draw(*object);
	}
	if (m_PulleyBlockA)
	{
		Statics::RenderWindow.draw(*m_PulleyBlockA);
	}
	if (m_PulleyBlockB)
	{
		Statics::RenderWindow.draw(*m_PulleyBlockB);
	}
	for (auto& object : m_Pigs)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Birds)
	{
		Statics::RenderWindow.draw(*object);
	}
	m_Catapult.DrawFront();

	Statics::RenderWindow.draw(VFX::GetInstance());
	Statics::RenderWindow.draw(GUI::GetInstance());

	if (m_PauseMenu)
	{
		Statics::RenderWindow.draw(*m_PauseMenu);
	}
}

void LevelThree::CreateCollisionLess()
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
		object->CreateBody();
	}

	m_Statics.emplace_back(new GameObject(*m_World, { 600, 10 }));
	m_Statics.back()->SetTexture("Diamond/BigWheel (1).png");
	m_Statics.back()->SetScale({ 0.25f,0.25f });
	m_Statics.back()->CreateBody();

	m_Statics.emplace_back(new GameObject(*m_World, { 1400, 10 }));
	m_Statics.back()->SetTexture("Diamond/BigWheel (1).png");
	m_Statics.back()->SetScale({ 0.25f,0.25f });
	m_Statics.back()->SetBodyType(b2_staticBody);
	m_Statics.back()->CreateBody();
}

void LevelThree::CreateBirds()
{
	m_Birds.emplace_back(new Bird(*m_World, { 190,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 150,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 110,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 70,566 }));
	m_Birds.emplace_back(new Bird(*m_World, { 30,566 }));
}

void LevelThree::CreatePigs()
{
	m_Pigs.emplace_back(new Pig(*m_World, { 900,350 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1100,350 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 1400,180 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 600,180 }));

	m_Pigs.emplace_back(new Pig(*m_World, { 1400,500 }));
	m_Pigs.emplace_back(new Pig(*m_World, { 600,500 }));
}

void LevelThree::CreateDestructables()
{
	m_PulleyBlockA = new Destructable(*m_World, { 600, 150 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::ICE);
	m_PulleyBlockA->SetRotation(90.0f);

	m_PulleyBlockB = new Destructable(*m_World, { 1400, 150 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::ICE);
	m_PulleyBlockB->SetRotation(-90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 900, 370 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1100, 370 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));

	m_Destructables.emplace_back(new Destructable(*m_World, { 850, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 950, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 1050, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1150, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::STONE));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 1180, 310 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 820, 310 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);

	m_Destructables.emplace_back(new Destructable(*m_World, { 600, 550 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1400, 550 }, Destructable::SHAPE::WIDE, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
}

void LevelThree::CreateJoints()
{
	b2PulleyJointDef pulleyJoint{};
	pulleyJoint.bodyA = m_PulleyBlockA->GetBody();
	pulleyJoint.bodyB = m_PulleyBlockB->GetBody();
	pulleyJoint.collideConnected = false;
	pulleyJoint.groundAnchorA.Set(600 / Statics::Scale, 80 / Statics::Scale);
	pulleyJoint.groundAnchorB.Set(1400 / Statics::Scale, 80 / Statics::Scale);
	pulleyJoint.lengthA = 150 / Statics::Scale;
	pulleyJoint.lengthB = 150 / Statics::Scale;

	JointManager::GetInstance().CreatePulleyJoint(pulleyJoint);
}

void LevelThree::CleanupDestroyedDestructables(std::vector<Destructable*>& _vector)
{
	GameLevel::CleanupDestroyedDestructables(_vector);
	if (m_PulleyBlockA)
	{
		if (m_PulleyBlockA->Destroy)
		{
			delete m_PulleyBlockA;
			m_PulleyBlockA = nullptr;
		}
	}
	if (m_PulleyBlockB)
	{
		if (m_PulleyBlockB->Destroy)
		{
			delete m_PulleyBlockB;
			m_PulleyBlockB = nullptr;
		}
	}
}
