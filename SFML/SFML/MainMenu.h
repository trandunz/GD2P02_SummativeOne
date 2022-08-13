#pragma once
#include "Level.h"
#include "Button.h"
#include "LevelManager.h"

class MainMenu :
    public Level
{
public:
    MainMenu();
    ~MainMenu();

    virtual void PollEvents(sf::Event& _event) override;
    virtual void Update() override;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void CreateMeshes();
    void CreateButtons();

    sf::Music m_Music;
    std::vector<Mesh*> m_Meshes{};
    std::vector<Button*> m_Buttons{};
};

