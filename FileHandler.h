#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <ostream>


class FileHandler {
private:

public:
	FileHandler();
	std::vector<int16_t> loadWav(std::string path);
	void saveWav(std::vector<int16_t> & samples, std::string path);
	void saveBac(std::vector<char> & file, std::string path);
};