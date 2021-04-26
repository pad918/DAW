#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "AudioPlaybackStream.h"
#include "Synth.h"
#include "SineWave.h"
#include "HarmonicForm.h"
#include "BassDrum.h"
#include "Sampler.h"
#include "DrumMachine.h"
#include "MIDI/Midi.h"

class DAW {
private:
	//Virtual functions
	sf::SoundStream * stream;
	std::vector<Synth *> synths;
	std::vector<Note> loadNotesFromTrack(TrackChunk &track, int timeDivision);
	std::vector<std::vector<Note>> splitMidiFile(std::list<TrackChunk> & tracks, int timeDivision);
	void addNoteToCorrectChannel(Note & note, std::vector<std::vector<Note>> & channels);
	float keyIdToFrequency(int id);
public:
	DAW();
	void update();
	void render(sf::RenderWindow & window);
	
};