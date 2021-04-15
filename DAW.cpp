#include "DAW.h"


DAW::DAW()
{
	//TMP CODE
	Synth * tmp = new SineWave(1000);
	sf::Time c1; c1 = sf::seconds(1.0f);
	sf::Time c2; c2 = sf::seconds(2.0f);
	sf::Time c3; c3 = sf::seconds(3.0f);
	sf::Time r1; r1 = sf::seconds(7.0f);
	sf::Time r2; r2 = sf::seconds(7.0f);
	sf::Time r3; r3 = sf::seconds(7.0f);
	tmp->noteHandler.addNote(c1, r1, 400);
	tmp->noteHandler.addNote(c2, r2, 500);
	tmp->noteHandler.addNote(c3, r3, 600);
	synths.push_back(tmp);
	//END TMP CODE

	stream = new AudioPlaybackStream(&synths);
	stream->play();
}

void DAW::update()
{

}

void DAW::render(sf::RenderWindow & window)
{

}

