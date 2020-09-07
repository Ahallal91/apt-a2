#include "Reader.h"
#include <fstream>
#include <iostream>

Reader::Reader() {}

Reader::~Reader() {}

// reads tiles from a text file and adds to the list
bool Reader::readTileBag(LinkedList& list, std::string fileName) {
	bool success = false;
	std::ifstream file;
	file.open(fileName);
	char c = ' ';

	if (file.is_open()) {
		success = true;
		// ensures last character isn't read twice
		while (file >> c) {
			list.addBack(c);
		}
		file.close();
	}
	return success;
}