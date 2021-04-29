#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DAW.h"

#define PANEL_TYPE 0
#define BUTTON_TYPE 0

class UI {
protected:
	DAW * daw = nullptr;
	UI * parent = nullptr;
	std::vector<UI *> children;
	sf::Vector2i pos, size;
	void updateArea();
	void drawChildren(std::vector<UI *> & UI_children, sf::RenderWindow & window);
public:
	UI(DAW* daw_ptr, UI* parent_ptr);
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void poll(sf::Vector2i mousePos, bool mouseClicked) = 0;
	void addElement(UI* UI_elemnt);
	void removeElement(UI* UI_element);
	void setColor(sf::Color color);
	void setArea(sf::Vector2i position, sf::Vector2i areaSize);
	sf::RectangleShape sprite; //INTE PUBLIC
	sf::Vector2i getAbsolutePosition();
	uint8_t type = 0;
};