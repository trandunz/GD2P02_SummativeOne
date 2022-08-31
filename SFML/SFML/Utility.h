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


