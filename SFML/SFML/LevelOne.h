#pragma once
#include <SFML/Audio.hpp>
#include "ContactListener.h"
#include "Statics.h"
#include "Catapult.h"
#include "Level.h"
#include "Pig.h"
#include "Destructable.h"

class LevelOne : public Level
{
public:
	LevelOne();
	virtual ~LevelOne();

	virtual void PollEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void CreateCollisionLess();
	void CreateStatics();
	void CreateBirds();
	void CreatePigs();
	void CreateDestructables();

	template <typename T>
	void CleanupVector(std::vector <T*>& _vector);
	void CleanupDestroyedGameObjects(std::vector <GameObject*>& _vector);
	void CleanupDestroyedPigs(std::vector <Pig*>& _vector);
	void CleanupDestroyedBirds(std::vector <Bird*>& _vector);
	void CleanupDestroyedDestructables(std::vector <Destructable*>& _vector);

	b2World* m_World;
	ContactListener m_ContactListener;
	Catapult m_Catapult{ { 225.0f, 520.0f } };

	std::vector<GameObject*> m_CollisionLess{};
	std::vector<GameObject*> m_Statics{};
	std::vector<Bird*> m_Birds{};
	std::vector<Pig*> m_Pigs{};
	std::vector<Destructable*> m_Destructables{};
};

inline void LevelOne::CleanupDestroyedGameObjects(std::vector<GameObject*>& _vector)
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

inline void LevelOne::CleanupDestroyedPigs(std::vector<Pig*>& _vector)
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

inline void LevelOne::CleanupDestroyedBirds(std::vector<Bird*>& _vector)
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

inline void LevelOne::CleanupDestroyedDestructables(std::vector<Destructable*>& _vector)
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

template<typename T>
inline void LevelOne::CleanupVector(std::vector<T*>& _vector)
{
	auto it = _vector.begin();
	while (it != _vector.end())
	{
		delete (*it);
		(*it) = nullptr;
		it = _vector.erase(it);
	}
}
