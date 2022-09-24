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
	static void InitTextures(std::vector<std::string> _texturesToPreload);
	static sf::Texture& LoadTexture(std::string _fileName);
	static void CleanupTextures();

private:
	inline static std::map<std::string, sf::Texture*> m_LoadedTextures;
};

