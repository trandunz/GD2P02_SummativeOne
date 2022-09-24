// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: PauseMenu.h 
// Description  : PauseMenu Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include "Button.h"
class PauseMenu : public sf::Drawable
{
public:
	PauseMenu();
	/// <summary>
	/// PauseMenu Destructor
	/// </summary>
	~PauseMenu();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void CreateButtons();

	std::vector<Button> m_Buttons{};
};

