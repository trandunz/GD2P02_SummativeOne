#pragma once
#include "Statics.h"

template<typename T>
inline void CleanupVector(std::vector<T*>& _vector)
{
	for (auto& item : _vector)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
	_vector.clear();
	_vector.resize(0);
}

template<typename T>
inline void CleanupQueue(std::queue<T*>& _queue)
{
	for (auto& item : _queue)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
	_queue.clear();
	_queue.resize(0);
}


