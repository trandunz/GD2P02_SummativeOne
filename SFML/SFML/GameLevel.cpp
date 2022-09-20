#include "GameLevel.h"
#include "AudioManager.h"
#include "JointManager.h"
#include "GUI.h"
#include "VFX.h"
#include "PauseMenu.h"
#include "TextureLoader.h"
#include "LevelCompleteMenu.h"

GameLevel::GameLevel()
{
	m_View.setSize(Statics::RenderWindow.getDefaultView().getSize());
	m_View.setCenter(Statics::RenderWindow.getDefaultView().getCenter());
	m_CameraStartPos = m_View.getCenter();
	m_CameraTargetPos = m_CameraStartPos;
	m_CameraTargetPos.x = 1000;
	Statics::RenderWindow.setView(m_View);

	AudioManager::StopMusic();
	m_World = new b2World({ 0,10.0f });
	m_World->SetContactListener(&m_ContactListener);
	JointManager::GetInstance().SetWorld(*m_World);

	GUI::GetInstance().CreateText("ScoreIndicator",
		{
			{1280 - 200.0f, 20.0f},
			"Score: 10000",
			sf::Color::White,
			sf::Color::Black
		});

	GUI::GetInstance().CreateText("ScoreValue",
		{
			{1280 - 75.0f, 20.0f},
			"100000",
			sf::Color::White,
			sf::Color::Black
		});

	GUI::GetInstance().CreateButton("PauseButton",
		{
			"",
			{30.0f, 30.0f},
			{0.5f,0.5f},
			[this]()
			{
				TogglePause();
			},
			&TextureLoader::LoadTexture("GUI/Pause.png")
		});

	m_Score = 0.0f;
	m_CameraLerpAmount = 0;
	m_FireTimer = m_FireTime;
}

GameLevel::~GameLevel()
{
	JointManager::GetInstance().ForceCleanupJoints();
	CleanupVector(m_Statics);
	CleanupVector(m_CollisionLess);
	CleanupVector(m_Birds);
	CleanupVector(m_Pigs);
	CleanupVector(m_Destructables);

	if (m_World)
		delete m_World;
	m_World = nullptr;

	VFX::GetInstance().CleanupElements();
	GUI::GetInstance().CleanupElements();

	if (m_PauseMenu)
	{
		delete m_PauseMenu;
		m_PauseMenu = nullptr;
	}

	if (m_LevelCompleteMenu)
	{
		delete m_LevelCompleteMenu;
		m_LevelCompleteMenu = nullptr;
	}
}

void GameLevel::PollEvents()
{
	if (m_LevelComplete)
	{

	}
	else
	{
		if (Statics::EventHandle.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				TogglePause();
			}
		}

		if (m_FireTimer <= 0)
		{
			if (Statics::EventHandle.type == sf::Event::MouseButtonPressed)
			{
				if (Statics::IsPaused == false)
				{
					if (m_NextBirdIndex < m_Birds.size())
						m_Catapult.LoadBird(*m_Birds[m_NextBirdIndex++]);
				}
			}
			if (Statics::EventHandle.type == sf::Event::MouseMoved)
			{
				if (Statics::IsPaused == false)
				{
					m_Catapult.MoveBird();
				}
			}
			if (Statics::EventHandle.type == sf::Event::MouseButtonReleased)
			{
				if (m_Catapult.IsLoaded())
				{
					if (m_Catapult.GetTrajectoryPoint(200).x > 500)
					{
						m_CameraLerpAmount = 0;
						m_FireTimer = m_FireTime;
					}

					for (int i = m_NextBirdIndex; i < m_Birds.size(); i++)
						m_Birds[i]->SetPosition(m_Birds[i]->GetPosition() + sf::Vector2f{ 40.0f,0.0f });
				}

				m_Catapult.ReleaseBird();
			}
		}
	}
}

void GameLevel::Update()
{
	m_World->Step(Statics::TimeScale / 60.0f, 10, 10);

	for (auto& staticObject : m_Statics)
	{
		staticObject->Update();
	}
	for (auto& bird : m_Birds)
	{
		bird->Update();
	}
	for (auto& pig : m_Pigs)
	{
		pig->Update();
	}
	for (auto& destructable : m_Destructables)
	{
		destructable->Update();
	}
	for (auto& collisionLess : m_CollisionLess)
	{
		collisionLess->Update();
	}

	CleanupDestroyedGameObjects(m_Statics);
	CleanupDestroyedDestructables(m_Destructables);
	CleanupDestroyedGameObjects(m_CollisionLess);
	CleanupDestroyedPigs(m_Pigs);
	CleanupDestroyedBirds(m_Birds);
	JointManager::GetInstance().CleanupMarkedJoints();

	if (m_FireTimer > 0)
	{
		if (m_CameraDelayTimer > 0.0f && m_CameraLerpAmount >= 1.0f)
		{
			m_CameraDelayTimer -= Statics::DeltaTime;
		}
		else
		{
			if (m_LerpRight)
			{
				m_CameraLerpAmount += (Statics::DeltaTime / m_FireTime) * 2;

				if (m_CameraLerpAmount >= 1.0f)
				{
					m_CameraLerpAmount = 1.0f;
					m_LerpRight = false;
					m_CameraDelayTimer = m_CameraReturnDelay;
				}
			}
			else
			{
				m_CameraLerpAmount -= (Statics::DeltaTime / m_FireTime) * 2;
				if (m_CameraLerpAmount <= 0.0f)
				{
					m_CameraLerpAmount = 0.0f;
					m_LerpRight = true;
				}
			}

			m_FireTimer -= Statics::DeltaTime;
		}
	}
	else
	{
		if (m_LevelComplete == false && m_Pigs.size() <= 0)
		{
			m_LevelComplete = true;
			m_LevelCompleteMenu = new LevelCompleteMenu();
		}
	}

	m_View.setCenter({
		std::lerp(m_CameraStartPos.x, m_CameraTargetPos.x, m_CameraLerpAmount)
		, std::lerp(m_CameraStartPos.y, m_CameraTargetPos.y, m_CameraLerpAmount) });

	VFX::GetInstance().Update();

	GUI::GetInstance().SetText("ScoreIndicator", "Score:");
	GUI::GetInstance().SetText("ScoreValue", FloatToString(GetScore(), 0));
}

void GameLevel::Draw()
{
	Statics::RenderWindow.setView(m_View);

	for (auto& object : m_CollisionLess)
	{
		Statics::RenderWindow.draw(*object);
	}
	for (auto& object : m_Statics)
	{
		Statics::RenderWindow.draw(*object);
	}

	m_Catapult.DrawBack();
	for (auto& object : m_Destructables)
	{
		Statics::RenderWindow.draw(*object);
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

	if (m_LevelCompleteMenu)
	{
		Statics::RenderWindow.draw(*m_LevelCompleteMenu);
	}
}

void GameLevel::ResetCameraReturnDelay()
{
	m_CameraDelayTimer = m_CameraReturnDelay;
}

float& GameLevel::GetScore()
{
	return m_Score;
}

void GameLevel::TogglePause()
{
	Statics::TogglePaused();
	if (Statics::IsPaused)
	{
		if (m_PauseMenu == nullptr)
			m_PauseMenu = new PauseMenu();

		GUI::GetInstance().GetButton("PauseButton")->SetTexture("GUI/Play.png");
	}
	else
	{
		if (m_PauseMenu)
		{
			delete m_PauseMenu;
			m_PauseMenu = nullptr;
		}

		GUI::GetInstance().GetButton("PauseButton")->SetTexture("GUI/Pause.png");
	}
}

void GameLevel::CreateCollisionLess()
{
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 1280 / 2,720 / 2 }));
	m_CollisionLess.back()->SetTexture("Background.jpg");
	m_CollisionLess.back()->SetScale({ 2.65f,2.65f });
	m_CollisionLess.emplace_back(new GameObject(*m_World, { 3 * (1280 / 2) ,720 / 2 }));
	m_CollisionLess.back()->SetTexture("Background.jpg");
	m_CollisionLess.back()->SetScale({ 2.65f,2.65f });
}

void GameLevel::CreateStatics()
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

void GameLevel::CreateBirds()
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

void GameLevel::CreatePigs()
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

void GameLevel::CreateDestructables()
{
	m_Destructables.emplace_back(new Destructable(*m_World, { 950, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1050, 470 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));
	m_Destructables.back()->SetRotation(90.0f);
	m_Destructables.emplace_back(new Destructable(*m_World, { 1000, 390 }, Destructable::SHAPE::PLANK, Destructable::TYPE::WOOD));

	m_Destructables.emplace_back(new Destructable(*m_World, { 900, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));
	m_Destructables.emplace_back(new Destructable(*m_World, { 1100, 620 }, Destructable::SHAPE::SQUARE, Destructable::TYPE::WOOD));
}

void GameLevel::CreateJoints()
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

void GameLevel::CleanupDestroyedGameObjects(std::vector<GameObject*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void GameLevel::CleanupDestroyedPigs(std::vector<Pig*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void GameLevel::CleanupDestroyedBirds(std::vector<Bird*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}

void GameLevel::CleanupDestroyedDestructables(std::vector<Destructable*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		if ((*it)->Destroy)
		{
			delete (*it);
			(*it) = nullptr;
			it = _vector.erase(it);
			continue;
		}
		it++;
	}
}
