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

void Pig::Start()
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

		VFX::GetInstance().CreateAndPlayTextEffect(
			{
				FloatToString(GetScoreValue(), 0),
				{_hitPos.x * Statics::Scale, _hitPos.y * Statics::Scale},
				_pointColor,
				{1.5f,1.5f}
			}, 1.0f);

		*LevelLoader::GetScore() += GetScoreValue();
	}
}

float Pig::GetScoreValue()
{
	return 5000.0f;
}
