#pragma once

class Level;
class LevelLoader
{
public:
	static void PollEvents();
	static void Update();
	static void Draw();
	
	static void LoadLevel(Level* _level);
	static void CleanupLevel();
private:
	static Level* CurrentLevel;
};
