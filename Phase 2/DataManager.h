#pragma once
#include "DEFS.h"
#include "Figures\CFigure.h"

/*
Abstract class to hold clipBoard
for Copy,Cut and Paste Actions
*/

class DataManager
{
protected:
	static std::vector<CFigure*> clipBoard; //static because we need one clipBoard for all actions
public:
	DataManager();
	static void addToClipBoard(CFigure*);//add element to clipBoard
	static void clearClipBoard();//clear the clipboard without deleting the pointers
	static void destroyClipBoard();//clear the clipboard and deleting pointers
	int getSize() const;//size of clipBoard, to avoid accidents while calling member functions of vector
	virtual ~DataManager() = 0;//to make it abstract
};

