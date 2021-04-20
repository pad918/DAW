#include "DAW.h"

DAW::DAW()
{
	//TEST MIDI
	Midi midi{ "badapple.mid" };
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
	std::vector <Synth *> tmp_synths;

	tmp_synths.push_back(new HarmonicForm()); // NOT USED
	tmp_synths.push_back(new HarmonicForm()); // NOT USED
	tmp_synths.push_back(new HarmonicForm()); // MAIN SYNTH 
	tmp_synths.push_back(new HarmonicForm()); // MAIN SYNTH
	tmp_synths.push_back(new HarmonicForm()); // PIANO
	tmp_synths.push_back(new HarmonicForm()); // Lead
	tmp_synths.push_back(new HarmonicForm()); // Lead
	tmp_synths.push_back(new HarmonicForm()); // Bass
	tmp_synths.push_back(new HarmonicForm()); // Lead
	tmp_synths.push_back(new HarmonicForm()); // Lead
	tmp_synths.push_back(new HarmonicForm()); // Lead
	tmp_synths.push_back(new Sampler("samples/bass_drum.wav")); // DRUM?
	//tmp_synths.push_back(new HarmonicForm());

	tmp_synths[0]->amplitude = 0.0f;
	tmp_synths[1]->amplitude = 0.0f;
	tmp_synths[2]->amplitude = 0.5f;
	tmp_synths[3]->amplitude = 0.5f;
	tmp_synths[4]->amplitude = 0.5f;
	tmp_synths[5]->amplitude = 0.5f;
	tmp_synths[6]->amplitude = 0.5f;
	tmp_synths[7]->amplitude = 0.5f;
	tmp_synths[8]->amplitude = 0.5f;
	tmp_synths[9]->amplitude = 0.5f;
	tmp_synths[10]->amplitude = 0.0f;
	tmp_synths[11]->amplitude = 0.2f;

	std::cout << "TRACK SIZE = " << tracks.size() << "\n";
	for (int i = 0; 0 < tracks.size() && i < tmp_synths.size(); ++i) {
		tmp_synths[i]->noteHandler.loadFromMidiTrack(tracks.front(), header.getDivision());
		synths.push_back(tmp_synths[i]);
		tracks.pop_front();
	}

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

