#include "UI.h"

void UI::updateArea()
{
	sprite.setPosition((sf::Vector2f)getAbsolutePosition());
	sprite.setSize((sf::Vector2f)size);
	//Update area of all children:
	for (auto & child : children) {
		child->updateArea();
	}
}

void UI::drawChildren(std::vector<UI*>& UI_children, sf::RenderWindow & window)
{
	for (auto child : UI_children) {
		child->draw(window);
	}
}

UI::UI(DAW * daw_ptr, UI * parent_ptr)
{
	daw = daw_ptr;
	parent = parent_ptr;
}

void UI::addElement(UI * UI_elemnt)
{
	children.push_back(UI_elemnt);
}

void UI::removeElement(UI * UI_element)
{
	for (int i = 0; i < children.size(); ++i) {
		if (UI_element == children[i]) {
			children.erase(children.begin() + i);
			i--;
		}
	}
}

void UI::setArea(sf::Vector2i position, sf::Vector2i areaSize)
{
	size = areaSize;
	pos = position;
	updateArea();
}

sf::Vector2i UI::getAbsolutePosition()
{
	if (parent == nullptr) {
		return pos;
	}
	return pos + parent->getAbsolutePosition();
}


