#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#define TO_BE_CLICKED 0
#define IS_CLICKED 1
#define WAS_CLICKED 2

//Define notes
#define A4 440.00f
#define B4 493.88f
#define C4 523.25f
#define D4 587.32f
#define E4 659.26f
#define F4 698.46f
#define G4 783.99f


class Note {
public:
	int keyNum = 0;
	int status = 0;
	sf::Time clickTime, releaseTime;
	bool isDead = false;
	float freq = 1000;
	float velocity = 1.0f;
	float getAmp(sf::Time globalPlayBackPostion, float attack_time, float decay_time);
};