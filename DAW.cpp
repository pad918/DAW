#include "DAW.h"

DAW::DAW()
{
	//TEST MIDI
	Midi midi{ "eternal.mid" };
	auto tracks =  midi.getTracks();
	auto& header = midi.getHeader();
	//auto& tracks =	f.getTracks();

	std::cout << "File read" << std::endl;
	std::cout << "File contents:" << std::endl;
	std::cout << "	Header:" << std::endl;
	std::cout << "		File format: " << (int)header.getFormat() <<
		"\n		Number of tracks: " << header.getNTracks() <<
		"\n		Time division: " << header.getDivision() << std::endl;

	//END
	//TMP CODE
	Synth * tmp = new HarmonicForm();
	Synth * tmp2 = new HarmonicForm();
	Synth * tmp3 = new HarmonicForm();
	tmp->amplitude = 0.3f;
	tmp2->amplitude = 0.75f;
	tmp3->amplitude = 0.75f;
	std::cout << "TRACK SIZE = " << tracks.size() << "\n";
	//tracks.pop_front();
	//tracks.pop_front();
	tmp->noteHandler.loadFromMidiTrack(tracks.front()); 
	//tracks.pop_front();
	//tmp3->noteHandler.loadFromMidiTrack(tracks.front()); 
	//tracks.pop_front();
	//tmp2->noteHandler.loadFromMidiTrack(tracks.front()); 
	//tmp->noteHandler.addNote(sf::seconds(1.0f), sf::seconds(2.5f), A4);
	//tmp->noteHandler.addNote(sf::seconds(1.5f), sf::seconds(2.5f), C4);
	//tmp->noteHandler.addNote(sf::seconds(2.0f), sf::seconds(2.5f), D4);
	synths.push_back(tmp);
	//synths.push_back(tmp2);
	//synths.push_back(tmp3);
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

