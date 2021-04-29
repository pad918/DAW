#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"
#include "Button.h"

class Panel : public UI {
protected:
	
public:
	Panel(DAW* daw_ptr, UI* parent_ptr) : UI(daw_ptr, parent_ptr) { type = PANEL_TYPE; };
	void setColor(sf::Color backgroundColor);
	virtual void draw(sf::RenderWindow & window);
	virtual void poll(sf::Vector2i mousePos, bool mouseClicked);
	virtual void handleButtons(std::vector<int> pressedButtons) = 0;
	sf::Color color;
};