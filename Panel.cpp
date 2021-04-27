#include "Panel.h"

void Panel::setColor(sf::Color backgroundColor)
{
	color = backgroundColor;
	sprite.setFillColor(color);
}

void Panel::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
	drawChildren(children, window);
}
