#pragma once
#include <SFML/Graphics.hpp>
#define TO_BE_CLICKED 0
#define IS_CLICKED 1
#define WAS_CLICKED 2


class Note {
public:
	int status = 0;
	sf::Time clickTime, releaseTime;
	float freq = 1000;
};