#ifndef READER_H
#define READER_H

#include "LinkedList.h"
#include <string>

class Reader {
public:
	Reader();
	~Reader();

	// adds each line of file to the linked list; used for reading in tile bag
	bool readTileBag(LinkedList& list, std::string fileName);

	// TODO add a method that takes in an 
	// array/vector/string to add to the list (save file)

private:
	

	

};

#endif // READER_H