#include "DAW.h"


DAW::DAW()
{
	stream = new AudioPlaybackStream();
	stream->play();
}

void DAW::update()
{

}

void DAW::render(sf::RenderWindow & window)
{

}

