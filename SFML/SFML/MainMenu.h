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
#include "Level.h"

class MainMenu : public Level
{
public:
    /// <summary>
    /// Main Menu Constructor
    /// </summary>
    MainMenu();
    /// <summary>
    /// MainMenu Destructor
    /// </summary>	
    ~MainMenu();

    /// <summary>
    /// Handles all sfml events such as mouse pressed
    /// </summary>
    virtual void PollEvents() override;
    /// <summary>
    /// Handles updating everything in the scene
    /// </summary>
    virtual void Update() override;
    /// <summary>
    /// Handles drawing everything in the scene
    /// </summary>
    virtual void Draw() override;

private:
    /// <summary>
    /// Handles the creation of all meshes
    /// </summary>
    void CreateMeshes();
    /// <summary>
    /// Handles the creation of all buttons
    /// </summary>
    void CreateButtons();
};

