#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"

class Panel : public UI {
private:
	sf::Color color;
public:
	Panel(DAW* daw_ptr, UI* parent_ptr) : UI(daw_ptr, parent_ptr) {};
	void setColor(sf::Color backgroundColor);
	virtual void draw(sf::RenderWindow & window);
};