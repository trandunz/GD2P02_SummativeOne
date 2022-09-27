// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: GameLevel.cpp 
// Description  : GameLevel Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "GameLevel.h"
#include "AudioManager.h"
#include "JointManager.h"
#include "GUI.h"
#include "VFX.h"
#include "PauseMenu.h"
#include "TextureLoader.h"
#include "LevelCompleteMenu.h"
#include "LevelFailedMenu.h"
#include "Utility.h"
#include "Pig.h"
#include "Destructable.h"

GameLevel::GameLevel()
{
	AudioManager::StopMusic();

	// Setup view
	m_View.setSize(Statics::RenderWindow.getDefaultView().getSize());
	m_View.setCenter(Statics::RenderWindow.getDefaultView().getCenter());
	Statics::RenderWindow.setView(m_View);

	// Setup camera 
	m_CameraStartPos = m_View.getCenter();
	m_CameraTargetPos = { 1000, m_CameraStartPos.y };

	// Setip b2World
	m_World = new b2World({ 0,10.0f });
	m_World->SetContactListener(&m_ContactListener);
	JointManager::GetInstance().SetWorld(*m_World);

	CreateGUIElements();
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
	{
		delete m_World;
		m_World = nullptr;
	}

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

	if (m_LevelFailedMenu)
	{
		delete m_LevelFailedMenu;
		m_LevelFailedMenu = nullptr;
	}
}

void GameLevel::PollEvents()
{
	// If level is complete and game is paused, resume play
	if (m_LevelComplete)
	{
		if (Statics::IsPaused)
		{
			TogglePause();
		}
	}
	else
	{
		// Pause / Resume if escape is pressed
		if (Statics::EventHandle.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				TogglePause();
			}
		}

		// If Camera is panning towards pigs and mouse button is pressed
		if (m_FireTimer > 0)
		{
			if (Statics::EventHandle.type == sf::Event::MouseButtonPressed)
			{
				if (Statics::IsPaused == false)
				{
					if (Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
					{
						if (m_Birds.size() > 0)
						{
							// Fire its special ability
							m_Birds[0]->SpecialAbility(m_Pigs, m_Destructables);
						}
					}
				}
			}
		}
		// Else if camera is still and looking at the birds
		else if (m_FireTimer <= 0)
		{
			// if mouse is pressed, load a bird
			if (Statics::EventHandle.type == sf::Event::MouseButtonPressed)
			{
				if (Statics::IsPaused == false)
				{
					if (Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
					{
						if (m_Birds.size() > 0)
						{
							m_Catapult.LoadBird(*m_Birds[0]);
						}
					}
				}
			}
			// if mouse is moved, move the currently loaded bird (if applicable)
			if (Statics::EventHandle.type == sf::Event::MouseMoved)
			{
				if (Statics::IsPaused == false)
				{
					m_Catapult.MoveBird();
				}
			}
			// If mouse is released, fire the loaded bird and begin camera pan / lerp
			if (Statics::EventHandle.type == sf::Event::MouseButtonReleased)
			{
				if (Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
				{
					if (m_Catapult.IsLoaded())
					{
						// Start camera lerp
						m_CameraLerpAmount = 0;
						m_FireTimer = m_FireTime;

						// Move all birds a bird width closer to the slingshot
						for (int i = 0; i < m_Birds.size(); i++)
							m_Birds[i]->SetPosition(m_Birds[i]->GetPosition() + sf::Vector2f{ 40.0f,0.0f });

						// Fire the loaded bird
						m_Catapult.ReleaseBird();
					}
				}
			}
		}
	}
}

void GameLevel::Update()
{
	// apply physics step
	m_World->Step(Statics::TimeScale / 60.0f, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	// Update everything
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

	CameraPanUpdate();

	HandleWinLossConditions();

	// Update the view too the lerped position of camera start and camera target
	m_View.setCenter({
		std::lerp(m_CameraStartPos.x, m_CameraTargetPos.x, m_CameraLerpAmount)
		, std::lerp(m_CameraStartPos.y, m_CameraTargetPos.y, m_CameraLerpAmount) });

	VFX::GetInstance().Update();

	UpdateLevelScoreGUI();

	HandleGarbageCollection();
}

void GameLevel::Draw()
{
	// Set to game view
	Statics::RenderWindow.setView(m_View);
	
	//
	// Draw all world elements
	//
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

	//
	// Draw all screen / GUI elements
	//
	Statics::RenderWindow.draw(VFX::GetInstance());
	Statics::RenderWindow.draw(GUI::GetInstance());
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

		// Update pause button texture
		GUI::GetInstance().GetButton("PauseButton")->SetTexture("GUI/Play.png");
	}
	else
	{
		if (m_PauseMenu)
		{
			delete m_PauseMenu;
			m_PauseMenu = nullptr;
		}

		// Update pause button texture
		GUI::GetInstance().GetButton("PauseButton")->SetTexture("GUI/Pause.png");
	}
}

void GameLevel::CreateCollisionLess()
{
	sf::Vector2f windowCenter = Statics::RenderWindow.getView().getCenter();
	windowCenter.y -= 720 / 6;

	// Create background
	m_CollisionLess.emplace_back(new GameObject(*m_World, windowCenter));
	m_CollisionLess.back()->SetTexture("Background.png");
	m_CollisionLess.emplace_back(new GameObject(*m_World, { windowCenter.x * 3, windowCenter.y }));
	m_CollisionLess.back()->SetTexture("Background.png");

	// Create grass
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

void GameLevel::CreateStatics()
{
	//
	// Create ground objects
	//
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

void GameLevel::CreateGUIElements()
{
	GUI::GetInstance().CreateText("ScoreIndicator", // Key
		{
			{1280 - 200.0f, 20.0f}, // Position
			"Score: 10000", // Text / label
		});

	GUI::GetInstance().CreateText("ScoreValue", // Key
		{
			{1280 - 75.0f, 20.0f}, // Position
			"100000", // Text / label
		});

	GUI::GetInstance().CreateButton("PauseButton", // Key
		{
			"", // Text / label
			{30.0f, 30.0f}, // Position
			{0.5f,0.5f}, // Scale
			[this]()
			{
				TogglePause(); // On Press Function
			},
			&TextureLoader::LoadTexture("GUI/Pause.png") // Texture
		});
}

void GameLevel::HandleGarbageCollection()
{
	CleanupDestroyedGameObjects(m_Statics);
	CleanupDestroyedDestructables(m_Destructables);
	CleanupDestroyedGameObjects(m_CollisionLess);
	CleanupDestroyedPigs(m_Pigs);
	CleanupDestroyedBirds(m_Birds);
	JointManager::GetInstance().CleanupMarkedJoints();
}

void GameLevel::CameraPanUpdate()
{
	// If bird has been fired
	if (m_FireTimer > 0)
	{
		// If camera return delay is active and camera has reached the end of its pan,
		// Reduce the camera return delay timer
		if (m_CameraDelayTimer > 0.0f && m_CameraLerpAmount >= 1.0f)
		{
			m_CameraDelayTimer -= Statics::DeltaTime;
		}
		else
		{
			// else if camera is lerping right,
			if (m_LerpRight)
			{
				// Increase lerp amount by fire time / rate of fire
				m_CameraLerpAmount += (Statics::DeltaTime / m_FireTime) * 2;

				// If lerp has reached its end, start camera return delay and lerp right to false
				if (m_CameraLerpAmount >= 1.0f)
				{
					m_CameraLerpAmount = 1.0f;
					m_LerpRight = false;
					m_CameraDelayTimer = m_CameraReturnDelay;
				}
			}
			else
			{
				// else, start panning left by reducing the lerp ratio
				m_CameraLerpAmount -= (Statics::DeltaTime / m_FireTime) * 2;

				// set lerp right for next shot if camera has returned to birds
				if (m_CameraLerpAmount <= 0.0f)
				{
					m_CameraLerpAmount = 0.0f;
					m_LerpRight = true;
				}
			}

			// Reduce the fire timer
			m_FireTimer -= Statics::DeltaTime;
		}
	}

	// If bird is moving and there are pigs alive, reset the camera return delay
	if (m_Birds.size() > 0)
	{
		if (Mag(m_Birds[0]->GetVelocity()) > 10.0f && m_Pigs.size() > 0)
		{
			ResetCameraReturnDelay();
		}
	}
}

void GameLevel::HandleWinLossConditions()
{
	if (m_FireTimer <= 0.0f)
	{
		if (m_LevelComplete == false && m_Pigs.size() <= 0)
		{
			m_LevelComplete = true;

			for (auto& bird : m_Birds)
				bird->AwardUnusedBirdScore();

			m_LevelCompleteMenu = new LevelCompleteMenu();
		}
		else if (m_LevelComplete == false && m_Birds.size() <= 0)
		{
			m_LevelComplete = true;
			m_LevelFailedMenu = new LevelFailedMenu();
		}
	}
}

void GameLevel::UpdateLevelScoreGUI()
{
	GUI::GetInstance().SetText("ScoreIndicator", "Score:");
	GUI::GetInstance().SetText("ScoreValue", FloatToString(GetScore(), 0));
}
