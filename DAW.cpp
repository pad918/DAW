#include "DAW.h"


DAW::DAW()
{
	//TMP CODE
	Synth * tmp = new HarmonicForm();
	tmp->noteHandler.addNote(sf::seconds(1.0f), sf::seconds(2.5f), A4);
	tmp->noteHandler.addNote(sf::seconds(1.5f), sf::seconds(2.5f), C4);
	tmp->noteHandler.addNote(sf::seconds(2.0f), sf::seconds(2.5f), D4);
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

