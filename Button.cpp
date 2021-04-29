#include "Button.h"

void Button::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
	drawChildren(children, window);
}

void Button::poll(sf::Vector2i mousePos, bool mouseClicked)
{
	auto absolutePos = getAbsolutePosition();
	bool mouseOverButton = mousePos.x > absolutePos.x && mousePos.x < absolutePos.x + size.x
		&& mousePos.y > absolutePos.y && mousePos.y < absolutePos.y + size.y;
	bool wasReleased = mouseClickedLastPoll && !mouseClicked;

	if (wasReleased && mouseOverButton) {
		wasClicked = true;
	}
	else {
		wasClicked = false;
	}

	mouseClickedLastPoll = mouseClicked;
}
