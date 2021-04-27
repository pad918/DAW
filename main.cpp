/*
A basic DAW made by Måns Abrahamsson
Project started: 2021-04-15

Progress:
2021-04-15: 267  lines
2021-04-20: 552  lines
2021-04-21: 638  lines
2021-04-26  1047 lines
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "DAW.h"
#include "UI.h"
#include "Panel.h"
#include "UI_factory.h"

int main() {
	DAW daw;
	/*********************************/
	UI_factory ui;
	UI * main_ui = ui.createPanel(&daw, nullptr, sf::Vector2i(0,0), sf::Vector2i(1000, 500), sf::Color(51,51,51));
	main_ui->addElement(ui.createPanel(&daw, main_ui, sf::Vector2i(50, 50), sf::Vector2i(50, 50), sf::Color::Red));
	/********************************/
	sf::RenderWindow window(sf::VideoMode(1000, 500), "DAW V_0.0");
	window.setFramerateLimit(60);
	int frame = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		daw.update();
		window.clear();
		daw.render(window);
		main_ui->draw(window);
		main_ui->setArea(sf::Vector2i(100 + 50*std::cosf(frame/1000.0f), 100 + 50*std::sinf(frame / 1000.0f)), sf::Vector2i(100, 100));
		window.display();
		frame++;
	}
	std::cout << "DAW was closed. Exeting.\n";
	return 0;
}