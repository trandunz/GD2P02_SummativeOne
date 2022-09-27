// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: TextureLoader.h 
// Description  : TextureLoader Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include <map>
#include "SFML/Graphics/Texture.hpp"

class TextureLoader
{
public:
	/// <summary>
	/// Pre Loads all the specified textures
	/// </summary>
	/// <param name="_texturesToPreload"></param>
	static void InitTextures(std::vector<std::string> _texturesToPreload);
	/// <summary>
	/// Loads and returns a texture at the specified file path
	/// </summary>
	/// <param name="_fileName"></param>
	/// <returns></returns>
	static sf::Texture& LoadTexture(std::string _fileName);
	/// <summary>
	/// Cleans up all loaded textures
	/// </summary>
	static void CleanupTextures();

private:
	inline static std::map<std::string, sf::Texture*> m_LoadedTextures;
};

