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

