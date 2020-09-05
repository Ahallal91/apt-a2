#include "Reader.h"
#include <fstream>
#include <iostream>

Reader::Reader() {}

Reader::~Reader() {}

bool Reader::readTileBag(LinkedList& list, std::string fileName) {
	bool success = false;
	std::ifstream inFile;
	inFile.open(fileName);


	if (inFile.good()) {
		while (!inFile.eof()) {
			std::string line;
			std::getline(inFile, line);
			list.addFront(line.at(0));
			std::cout << "Read: " << line << std::endl;
		}
	}

	inFile.close();

}