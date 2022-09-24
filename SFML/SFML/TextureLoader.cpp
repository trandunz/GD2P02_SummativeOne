// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: TextureLoader.cpp 
// Description  : TextureLoader Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz


#include "TextureLoader.h"

void TextureLoader::InitTextures(std::vector<std::string> _texturesToPreload)
{
    for (auto& location : _texturesToPreload)
    {
        LoadTexture(location);
    }
}

sf::Texture& TextureLoader::LoadTexture(std::string _fileName)
{
    if (m_LoadedTextures[_fileName] != nullptr)
    {
        return *m_LoadedTextures[_fileName];
    }

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("Resources/Sprites/" + _fileName);
    m_LoadedTextures[_fileName] = texture;
    texture = nullptr;

    return *m_LoadedTextures[_fileName];
}

void TextureLoader::CleanupTextures()
{
    for (auto& texture : m_LoadedTextures)
    {
        if (texture.second != nullptr)
        {
            delete texture.second;
            texture.second = nullptr;
        }
    }
    m_LoadedTextures.clear();
}
