#include "FileHandler.h"
#include <fstream>
#include <iostream>

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

// reads tiles from a text file and adds to the list
bool FileHandler::readTileBag(LinkedList& list, std::string fileName) {
	bool success = false;
	std::ifstream file;
	file.open(fileName);
	char c = ' ';

	if (file.is_open()) {
		success = true;
		// ensures last character isn't read twice
		while (file >> c) {
			list.addFront(c);
		}
		file.close();
	}
	return success;
}

bool FileHandler::fileExists(std::string fileName) {
	std::ifstream file(fileName);
	return file.good();
}

bool FileHandler::isAzulGame(std::string fileName) {
	// TODO check that the file is azul game (.azul extensions and contents)
	return false;
}