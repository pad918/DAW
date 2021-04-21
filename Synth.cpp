#include "Synth.h"

std::vector<float> Synth::loadSamples(std::string path)
{
	FileHandler file;
	auto samples = file.loadWav(path);
	std::vector<float> outputSamples;
	if (samples.size() == 0) {
		std::cout << "ERROR: Failed to load audio file\n";
		return outputSamples;
	}
	for (auto & sample : samples) {
		outputSamples.push_back((float)sample / 32768.f);
	}
	return outputSamples;
}
