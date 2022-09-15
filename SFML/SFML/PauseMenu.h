#pragma once
#include "Button.h"
class PauseMenu : public sf::Drawable
{
public:
	PauseMenu();
	~PauseMenu();

	void PollEvents();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void CreateButtons();

	std::vector<Button> m_Buttons{};
};

