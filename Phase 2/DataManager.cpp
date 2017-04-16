#include "DataManager.h"


std::vector<CFigure*> DataManager::clipBoard;//initiate static vector
DataManager::DataManager()
{
}

void DataManager::addToClipBoard(CFigure* added) {
	clipBoard.push_back(added);
}

void DataManager::clearClipBoard() {
	clipBoard.clear();
}

void DataManager::destroyClipBoard() {
	for (int i = 0; i < clipBoard.size(); i++)	//traverse clipboard and remove all elements
		delete clipBoard[i];
	clearClipBoard();	//then clear the vector as all
}

int DataManager::getSize() const{
	return clipBoard.size();	//to avoid accidents while calling member functions of vector
}
DataManager::~DataManager()
{
}
