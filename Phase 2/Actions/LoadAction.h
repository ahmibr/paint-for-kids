#pragma once

#include "Action.h"
#include <fstream>
using namespace std;
class LoadAction : public Action
{
	ifstream loadfile;
public:
	LoadAction(ApplicationManager *pApp);
	~LoadAction();

	virtual void Execute();

	virtual void ReadActionParameters();

	void Undo();
	void Redo();



};

