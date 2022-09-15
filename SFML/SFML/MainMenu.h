#pragma once
#include "LevelLoader.h"
#include "Level.h"

class MainMenu : public Level
{
public:
    MainMenu();
    ~MainMenu();

    virtual void PollEvents() override;
    virtual void Update() override;
    virtual void Draw() override;

private:
    void CreateMeshes();
    void CreateButtons();
};

