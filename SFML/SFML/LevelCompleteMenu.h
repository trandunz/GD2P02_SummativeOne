#pragma once
#include "Button.h"
class LevelCompleteMenu : public sf::Drawable
{
public:
	LevelCompleteMenu();
	~LevelCompleteMenu();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void CreateButtons();

	std::vector<Button> m_Buttons{};
};

