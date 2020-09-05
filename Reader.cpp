#include "Reader.h"
#include <fstream>
#include <iostream>

Reader::Reader() {}

Reader::~Reader() {}

bool Reader::readTileBag(LinkedList& list, std::string fileName) {
	bool success = false;
	std::ifstream file;
	file.open(fileName);
	char c = ' ';

	if (file.is_open()) {
		success = true;
		// ensures last character isn't read twice
		while (file >> c) {
			list.addFront(c);
			std::cout << "Character read: " << c << std::endl;
		}

		file.close();

	}
	return success;
}