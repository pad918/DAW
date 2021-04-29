#include "Panel.h"
#include <iostream>

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

void Panel::poll(sf::Vector2i mousePos, bool mouseClicked)
{
	std::vector<int> pressedButtons;
	int buttonNumber = 0;
	for (auto child : children) {
		if (child->type == BUTTON_TYPE) {
			child->poll(mousePos, mouseClicked);
			if (((Button*)child)->wasClicked) {
				pressedButtons.push_back(buttonNumber);
				if (daw->stream->getStatus() == sf::SoundSource::Status::Playing) {
					daw->stream->pause();
				}
				else if (daw->stream->getStatus() == sf::SoundSource::Status::Paused) {
					daw->stream->play();
				}
				
			}
			buttonNumber++;
		}
	}
	handleButtons(pressedButtons);
}
