/*
A basic DAW made by Måns Abrahamsson
Project started: 2021-04-15

Progress:
2021-04-15: 60 lines
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "DAW.h"

int main() {
	DAW daw;
	sf::RenderWindow window(sf::VideoMode(500, 250), "DAW V_0.0");
	while (window.isOpen()) {
		daw.update();
		window.clear();
		daw.render(window);
		window.display();
	}
	std::cout << "DAW was closed. Exeting.\n";
	return 0;
}