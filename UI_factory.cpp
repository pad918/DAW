#include "UI_factory.h"

UI * UI_factory::createPanel(DAW * daw, UI* parent, sf::Vector2i pos, sf::Vector2i size, sf::Color color)
{
	UI * element = new Panel(daw, parent);
	element->setArea(pos, size);
	element->sprite.setFillColor(color);
	return element;
}
