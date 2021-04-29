#include "DAW.h"


std::vector<Note> DAW::loadNotesFromTrack(TrackChunk & track, int timeDivision)
{
	std::vector<Note> notes;
	float tickFraction = timeDivision * 2.0f;
	long time = 0;
	int program_change = 0;
	std::vector<Note> clickedNotes;
	auto events = track.getEvents();
	for (auto event : events) {
		const Event * ev = event.getEvent();
		if (ev->getType() == MidiType::EventType::MidiEvent) {
			const MidiEvent * tmp = (MidiEvent*)ev;
			auto status = tmp->getStatus();
			int deltaTime = event.getDeltaTime().getData();
			int velocity = tmp->getData() & 0b1111111;
			time += deltaTime;
			if (status == MidiType::NoteOn && velocity != 0) {
				sf::Time clickTime = sf::seconds(time / tickFraction);
				Note note;
				note.velocity = velocity / 127.0f;
				note.clickTime = clickTime;
				note.keyNum = (int)tmp->getNote();
				note.freq = keyIdToFrequency((int)tmp->getNote());
				note.channel = tmp->getChannel();
				note.instrument = program_change;
				clickedNotes.push_back(note);
			}
			if (status == MidiType::NoteOff || (status == MidiType::NoteOn && velocity == 0)) {
				for (int i = 0; i < clickedNotes.size(); ++i) {
					auto & note = clickedNotes[i];
					if (note.keyNum == (int)tmp->getNote()) {
						sf::Time relTime = sf::seconds(time / tickFraction); //200
						note.releaseTime = relTime;
						notes.push_back(note);
						clickedNotes.erase(clickedNotes.begin() + i);
						i--;
					}
				}
			}
			if (status == MidiType::ProgramChange) {
				int a = program_change;
				program_change = tmp->getData();
			}
		}
	}
	//Sort notes based on startTime:
	std::sort(notes.begin(), notes.end(),
		[](const Note & a, const Note & b) -> bool
	{
		return a.clickTime < b.clickTime;
	});
	return notes;
}

std::vector<std::vector<Note>> DAW::splitMidiFile(std::list<TrackChunk>& tracks, int timeDivision)
{
	std::vector<std::vector<Note>> channelTracks;
	for (auto & track : tracks) {
		auto notes = loadNotesFromTrack(track, timeDivision); 
		std::vector<std::vector<Note>> channels;
		bool isChanelLoaded = false;
		
		for (auto & note : notes) {
			addNoteToCorrectChannel(note, channels);
		}
		
		for (auto & channel : channels) {
			channelTracks.push_back(channel);
		}
	}
	return channelTracks;
}

void DAW::addNoteToCorrectChannel(Note & note, std::vector<std::vector<Note>>& channels)
{
	for (int i = 0; i < channels.size(); ++i) {
		if (channels[i].size() > 0) {
			if (note.channel == channels[i][0].channel) {
				channels[i].push_back(note);
				return;
			}
		}
	}
	//If note channel not in channels, add it.
	std::vector<Note> tmp; 
	tmp.push_back(note);
	channels.push_back(tmp);
}

float DAW::keyIdToFrequency(int id)
{
	int octave = (id / 12) - 1;
	int key = id % 12;

	//float octaveCoeff = std::pow(2, octave - 4);
	//FASTER THAN std::POW
	float octaveCoeff = 1;
	int exponent = octave - 4;
	if (exponent == 0) {
		octaveCoeff = 1;
	}
	else if (exponent < 0) {
		while (exponent < 0) {
			octaveCoeff *= 0.5f;
			exponent++;
		}
	}
	else {
		while (exponent > 0) {
			octaveCoeff *= 2.0f;
			exponent--;
		}
	}

	switch (key) {
	case 0: //  C
		return 261.63f * octaveCoeff;
	case 1: //  C#
		return 277.18f * octaveCoeff;
	case 2: //  D
		return 293.66f * octaveCoeff;
	case 3: //  D#
		return 311.13f * octaveCoeff;
	case 4: //  E
		return 329.63f * octaveCoeff;
	case 5: //  F
		return 349.23f * octaveCoeff;
	case 6: //  F#
		return 369.99f * octaveCoeff;
	case 7: //  G
		return 391.99f * octaveCoeff;
	case 8: //  G#
		return 415.30f * octaveCoeff;
	case 9: //  A
		return 440.00f * octaveCoeff;
	case 10: // A#
		return 466.16f * octaveCoeff;
	case 11: // B
		return 493.88f * octaveCoeff;
	}
	std::cout << "ERROR: not real key\n";
	return -1;
}

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

	 
	auto channels = splitMidiFile(tracks, header.getDivision());
	std::cout << "Channel size = " << channels.size() << "\n";
	std::vector <Synth *> tmp_synths;
	for (auto & channel : channels) {
		int instrument	=	channel[0].instrument;
		int noteChannel =	channel[0].channel;
		std::cout << "Added channel with " << channel.size() << " notes | instrument = ";
		if (noteChannel != 9) {
			
			if (instrument != 0) {
				tmp_synths.push_back(new HarmonicForm());
				tmp_synths.back()->noteHandler.setNotes(channel);
				tmp_synths.back()->amplitude = 0.5f;
			}
			std::cout << tmp_synths.back()->noteHandler.getInstrumentName() << "\n";
		}
		else {
			tmp_synths.push_back(new DrumMachine());
			tmp_synths.back()->noteHandler.setNotes(channel);
			tmp_synths.back()->amplitude = 0.25f;
			std::cout << tmp_synths.back()->noteHandler.getInstrumentName() << "\n";
		}
	}
	for (auto & synth : tmp_synths) {
		synths.push_back(synth);
	}

	stream = new AudioPlaybackStream(&synths);
	stream->play();
}

void DAW::update()
{

}

void DAW::render(sf::RenderWindow & window)
{

}

