#include "SingleFactory.h"
#include "BST.h"

SingleFactory::SingleFactory() {
    this->singleFactory = new BST();
    this->size = 0;
}

SingleFactory::~SingleFactory() {
    delete singleFactory;
}

void SingleFactory::clear() {
    singleFactory->clear();
    size = 0;
}

int SingleFactory::length() {
    return this->size;
}

bool SingleFactory::empty() {
    bool retValue = false;
    if (singleFactory->getRootValue() == '\0' && size == 0) {
        retValue = true;
    }

    return retValue;
}

bool SingleFactory::contains(const char tile) const {
    return singleFactory->contains(tile);
}

bool SingleFactory::add(const char tile) {
    bool retValue = false;
    if(size < 4) {
        singleFactory->add(tile);
        size++;
        retValue = true;
    }
    return retValue;
}

char SingleFactory::get(const char tile) const {
    char retValue = '\0';
    if (singleFactory->get(tile) != nullptr) {
        retValue = singleFactory->get(tile)->data;
    }
    return retValue;
}

bool SingleFactory::remove(const char tile) {
    bool retValue = false;
    if(size >= 0) {
        singleFactory->remove(tile);
        size--;
        retValue = true;
    }
    return retValue;
}

char SingleFactory::getRemaining() {
    char retValue = '\0';
    if(size >= 0) {
        retValue = singleFactory->getRootValue();
    }
    return retValue;
}

std::string SingleFactory::toString() {
    return singleFactory->dfs();
}

int SingleFactory::getTileCount(const char tile) {
    return singleFactory->count(tile);
}