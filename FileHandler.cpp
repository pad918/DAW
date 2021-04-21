#include "FileHandler.h"
#define U (unsigned char)

FileHandler::FileHandler()
{

}

std::vector<int16_t> FileHandler::loadWav(std::string path)
{

	unsigned int fileSize = 0;
	unsigned int channels = 0;
	unsigned int sampleRate = 0;
	unsigned int formatType = 0;
	unsigned int formatDataLength = 0;
	unsigned int bitRate = 0;
	unsigned int bitsPerSample = 0;
	unsigned int bitSampleDiv8 = 0;
	unsigned int dataSize = 0;
	unsigned int dataStartPos = 0;
	std::ifstream infile(path);

	//get length of file
	infile.seekg(0, std::ios::end);
	size_t length = infile.tellg();
	infile.seekg(0, std::ios::beg);
	if (length < 45 || length > 100000000) {
		std::cout << "ERROR: file is too big or too small\n";
		return std::vector<int16_t>();
	}
	char* buffer = new char[length];
	infile.read(buffer, length);

	//Print header:
	//for (int i = 0; i < 44; ++i) {
	//	std::cout << buffer[i] << "|";
	//	if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 21 || i == 23 || i == 27 || i == 31 || i == 33 || i == 35 || i == 39 || i == 43) {
	//		std::cout << "\n";
	//	}
	//}
	//std::cout << "\n";

	//File size
	for (int i = 4; i < 8; ++i)
		fileSize += U buffer[i] << 8 * (i - 4);

	formatDataLength = (U buffer[19] << 24) + (U buffer[18] << 16) + (U buffer[17] << 8) + U buffer[16];
	formatType = (U buffer[21] << 8) + U buffer[20];
	channels = (U buffer[23] << 8) + U buffer[22];
	sampleRate = (U buffer[27] << 24) + (U buffer[26] << 16) + (U buffer[25] << 8) + U buffer[24];

	//BitRate
	for (int i = 28; i < 32; ++i)
		bitRate += U buffer[i] << 8 * (i - 28);

	bitSampleDiv8 = (U buffer[33] << 8) + U buffer[32];

	bitsPerSample = (U buffer[35] << 8) + U buffer[34];
	//dataStartPos  = (U buffer[39] << 24) + (U buffer[38] << 16) + (U buffer[37] << 8) + U buffer[36];
	for (int b = 36; b < fileSize - 4; b++) {
		if (buffer[b] == 'd' && buffer[b + 1] == 'a' && buffer[b + 2] == 't' && buffer[b + 3] == 'a') {
			dataStartPos = b + 4;
			break;
		}
	}
	dataSize = (U buffer[dataStartPos + 3] << 24) + (U buffer[dataStartPos + 2] << 16) + (U buffer[dataStartPos + 1] << 8) + U buffer[dataStartPos];

	//std::cout << "Sample rate = " << sampleRate << " | channels = " << channels << " | format data length = " << formatDataLength << 
	//	" | fileSize = " << (fileSize/1000000.0f) << "MB\n" << " | formatType = " << formatType << " | bitRate = " << bitRate <<
	//	" | bits per sample = " << bitsPerSample << "\n" << " | data start pos = " << dataStartPos << " | data size = " << dataSize <<
	//	" | dataChanBitDiv8 = " << bitSampleDiv8 << "\n";

	//std::cout << "Loading file...\n";
	//Read one of the channels
	std::vector<int16_t> samples;
	samples.resize(((dataSize) / (2 * channels)));
	int ittr = 0;
	int sizeOfSamples = samples.size();
	for (int i = dataStartPos + 4; i < length && ittr < sizeOfSamples; i += channels * 2) {
		if (i % 5000000 == 0) {
			//std::cout << 100.0f * i / (float)length << "%\n";
		}
		uint16_t tmp = (U(buffer[i + 1]) << 8) + U buffer[i];
		samples[ittr] = (int16_t)tmp;
		ittr++;
	}
	return samples;
}

void FileHandler::saveWav(std::vector<int16_t>& samples, std::string path)
{
	//Endast för en kanals ljud
	std::ofstream OutFile;
	OutFile.open(path, std::ios::out | std::ios::binary);
	int size = samples.size() * 2 + 44;
	char* buffer = new char[size];
	unsigned int fileSize = size;
	unsigned int channels = 1;
	unsigned int sampleRate = 44100; //44100
	unsigned int formatType = 1;
	unsigned int bitRate = 176400 / 2;
	unsigned int bitsPerSample = 16;
	unsigned int dataSize = size - 44;



	//RIFF MARKER
	buffer[0] = 'R';
	buffer[1] = 'I';
	buffer[2] = 'F';
	buffer[3] = 'F';

	//File size:
	for (int i = 4; i < 8; ++i)
		buffer[i] = (char)((fileSize >> (8 * (i - 4))) & 0b11111111);

	//WAVE MARKER
	buffer[8] = 'W';
	buffer[9] = 'A';
	buffer[10] = 'V';
	buffer[11] = 'E';

	//fmt marker:
	buffer[12] = 'f';
	buffer[13] = 'm';
	buffer[14] = 't';
	buffer[15] = ' ';

	//Length?
	buffer[16] = 16;
	buffer[17] = 0;
	buffer[18] = 0;
	buffer[19] = 0;

	//PCM
	buffer[20] = 1;
	buffer[21] = 0;

	//Channles
	buffer[22] = (char)(channels & 0b11111111);
	buffer[23] = (char)(channels >> 8);

	//Write sample rate to metadata
	for (int i = 24; i < 28; ++i)
		buffer[i] = (char)((sampleRate >> (8 * (i - 24))) & 0b11111111);

	//Write bitrate:
	for (int i = 28; i < 32; ++i)
		buffer[i] = (char)((bitRate >> (8 * (i - 28))) & 0b11111111);

	//bits per sample / 8
	buffer[32] = 2; // ändra
	buffer[33] = 0;

	//Bits per sample
	buffer[34] = (char)(bitsPerSample & 0b11111111);
	buffer[35] = (char)(bitsPerSample >> 8);

	//Data header
	buffer[36] = 'd';
	buffer[37] = 'a';
	buffer[38] = 't';
	buffer[39] = 'a';

	//data size
	for (int i = 40; i < 44; ++i)
		buffer[i] = (char)(dataSize >> (8 * (i - 40)));

	//Write raw samples
	int ittr = 0;
	for (int i = 44; i < size; i += 2) {
		buffer[i] = (char)(samples[ittr] & 0xFF);
		buffer[i + 1] = (char)((samples[ittr] >> 8) & 0xFF);
		ittr++;
	}
	OutFile.write(buffer, size);
	OutFile.close();
	std::cout << "Wrote wav file " << path << " | size = " << (size) << "\n";
}

void FileHandler::saveBac(std::vector<char>& file, std::string path)
{

}
