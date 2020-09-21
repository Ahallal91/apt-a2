#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "LinkedList.h"
#include <string>

class FileHandler {
public:
	FileHandler();
	~FileHandler();

	// adds each line of file to the linked list; used for reading in tile bag
	bool readTileBag(LinkedList& list, std::string fileName);

	// TODO add a method that takes in an 
	// array/vector/string to add to the list (save file)

	// Checks if a file exists
	bool fileExists(std::string fileName);

private:
	

	

};

#endif // FILE_HANDLER_H