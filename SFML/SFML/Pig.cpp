// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Pig.cpp 
// Description  : Pig Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "Pig.h"
#include "VFX.h"
#include "LevelLoader.h"

Pig::Pig(b2World& _world, sf::Vector2f _startPos, float _maxHP)
	: GameObject(_world, _startPos)
{
	m_b2UserData.identifier = "Pig";
	m_b2UserData.data = reinterpret_cast<uintptr_t>(this);

	m_MaxHealth = _maxHP;
	m_CurrentHealth = m_MaxHealth;

	SetTexture("Pig.png");
	m_Mesh->SetScale({ 0.5f, 0.5f });

	SetShapeType(BODYSHAPE::CIRCLE);
	SetBodyType(b2_dynamicBody);
	CreateBody();
}

Pig::~Pig()
{
}

void Pig::Update()
{
	if (m_DamageTimer > 0.0f)
		m_DamageTimer -= Statics::DeltaTime;

	GameObject::Update();

	if (m_CurrentHealth <= 0.0f)
		Destroy = true;
}

void Pig::TakeDamage(float _amount)
{
	if (m_DamageTimer <= 0.0f)
	{
		m_DamageTimer = m_DamageInterval;

		m_CurrentHealth -= _amount;

		if (m_CurrentHealth < 0.0f)
			m_CurrentHealth = 0.0f;
	}
}

void Pig::TakeDamage(float _amount, b2Vec2 _hitPos, sf::Color _pointColor)
{
	if (m_DamageTimer <= 0.0f)
	{
		m_DamageTimer = m_DamageInterval;

		m_CurrentHealth -= _amount;

		if (m_CurrentHealth < 0.0f)
			m_CurrentHealth = 0.0f;

		// Make a score text effect
		VFX::GetInstance().CreateAndPlayTextEffect(
			{
				FloatToString(GetScoreValue(), 0),  // Text / label
				{_hitPos.x * Statics::Scale, _hitPos.y * Statics::Scale}, // Pos
				_pointColor, // Color
				{1.5f,1.5f} // Scale
			}, 1.0f); // Lifetime

		// Add the score
		*LevelLoader::GetScore() += GetScoreValue();
	}
}

float Pig::GetScoreValue()
{
	return 5000.0f;
}
