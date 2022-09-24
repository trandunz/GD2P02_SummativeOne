// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: MainMenu.h 
// Description  : MainMenu Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "LevelLoader.h"
#include "Level.h"

class MainMenu : public Level
{
public:
    MainMenu();
    /// <summary>
    /// MainMenu Destructor
    /// </summary>	
    ~MainMenu();

    virtual void PollEvents() override;
    virtual void Update() override;
    virtual void Draw() override;

private:
    void CreateMeshes();
    void CreateButtons();
};

