// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: Utility.h 
// Description  : Utility Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Statics.h"

/// <summary>
/// Cleans up a vector of templated pointers
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_vector"></param>
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

/// <summary>
/// Cleans up a queue of templated pointers
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_queue"></param>
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

/// <summary>
/// Cleans up a map of key and templated values
/// </summary>
/// <typeparam name="K"></typeparam>
/// <typeparam name="V"></typeparam>
/// <param name="_map"></param>
template<typename K, typename V>
inline void CleanupMap(std::map<K, V*>& _map)
{
	for (auto& item : _map)
	{
		if (item)
		{
			delete item;
			item = nullptr;
		}
	}
	_map.clear();
}

/// <summary>
/// Cleans up a map of key and values pairs
/// </summary>
/// <typeparam name="K"></typeparam>
/// <typeparam name="V"></typeparam>
/// <param name="_map"></param>
template<typename K, typename V>
inline void CleanupMap(std::map<K, V>& _map)
{
	_map.clear();
}


