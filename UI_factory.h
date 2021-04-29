#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"
#include "Panel.h"
#include "DAW.h"
#include "SynthPanel.h"

class UI_factory {
private:

public:
	//UI * createPanel(DAW * daw, UI* parent, sf::Vector2i pos, sf::Vector2i size, sf::Color color);
	UI * createSynthList(DAW * daw, UI* parent, sf::Vector2i pos, sf::Vector2i size, sf::Color color);
};