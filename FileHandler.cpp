#include <fstream>

#include "FileHandler.h"

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

// reads tiles from a text file and adds to the list
bool FileHandler::readTileBag(LinkedList& list, std::string& listString, std::string fileName) {
	bool success = false;
	std::ifstream file;
	file.open(fileName);
	char c = ' ';

	if (file.is_open()) {
		success = true;
		// ensures last character isn't read twice
		while (file >> c) {
			list.addBack(c);
			listString.append(1, c);
		}
		file.close();
	}
	return success;
}

bool FileHandler::fileExists(std::string fileName) {
	std::ifstream file(fileName);
	return file.good();
}