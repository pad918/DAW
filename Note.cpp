#include "Note.h"

float Note::getAmp(sf::Time globalPlayBackPostion, float attack_time, float decay_time)
{
	sf::Time timeSinceClick = globalPlayBackPostion - clickTime;
	if (timeSinceClick.asSeconds() < attack_time) {
		return (timeSinceClick.asSeconds() / attack_time); //Linear interpolation (Should it be linear?)
	}
	if (WAS_CLICKED == status) {
		sf::Time timeSinceReleased = globalPlayBackPostion - releaseTime;
		float amplitude = 1.0f - (timeSinceReleased.asSeconds() / decay_time);
		if (amplitude < 0) {
			isDead = true;
			return 0;
		}
		return amplitude;
	}
	return 1.0f;
}
