#pragma once
#include "UI.h"
#include <SFML/Graphics.hpp>

class Button : public UI {
private:
	bool mouseClickedLastPoll = false;
public:
	Button(DAW* daw_ptr, UI* parent_ptr) : UI(daw_ptr, parent_ptr) { type = BUTTON_TYPE; };
	virtual void draw(sf::RenderWindow & window);
	virtual void poll(sf::Vector2i mousePos, bool mouseClicked);
	bool wasClicked = false;
};