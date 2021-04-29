#include "UI_factory.h"

//UI * UI_factory::createPanel(DAW * daw, UI* parent, sf::Vector2i pos, sf::Vector2i size, sf::Color color)
//{
//	UI * element = new Panel(daw, parent);
//	element->setArea(pos, size);
//	element->sprite.setFillColor(color);
//	return element;
//}

UI * UI_factory::createSynthList(DAW * daw, UI * parent, sf::Vector2i pos, sf::Vector2i size, sf::Color color)
{
	UI * synthList = new SynthPanel(daw, parent);
	synthList->setColor(sf::Color::Red);
	synthList->setArea(pos, sf::Vector2i(300, daw->synths.size() * 55 + 15));
	for (int i = 0; i < daw->synths.size(); ++i) {
		sf::Vector2i childPos = sf::Vector2i(10, 55*i+10);
		UI * button = new Button(daw, synthList);
		button->setArea(childPos, sf::Vector2i(250, 50));
		button->setColor(sf::Color(255, 50 * i, 145));
		synthList->addElement(button);
	}
	
	return synthList;
}
