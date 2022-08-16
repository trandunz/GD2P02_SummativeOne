#pragma once
#include <vector>
#include "Button.h"
#include "LevelLoader.h"
#include "Level.h"
#include "Mesh.h"

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

    std::vector<Mesh> m_Meshes{};
    std::vector<Button> m_Buttons{};
};

