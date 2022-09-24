// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: AudioManager.h 
// Description  : AudioManager Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include <SFML/Audio.hpp>
#include <map>

class AudioManager
{
public:
	static void PlayMusic(std::string _song, bool _loop = true);
	static void PauseMusic();
	static void StopMusic();
	static void CreateAudioSource(std::string _key);
	static void CreateAudioSource(std::string _key, std::string _sound);
	static void PlayAudioSource(std::string _key);
	static sf::SoundBuffer& LoadSound(std::string _sound);
	static void SetSound(std::string _audioSource, std::string _sound);

	static void Cleanup();
private:
	inline static sf::Music m_Jutebox;
	inline static std::map<std::string, sf::Sound*> m_AudioSources;
	inline static std::map<std::string, sf::SoundBuffer*> m_LoadedSounds;
};

