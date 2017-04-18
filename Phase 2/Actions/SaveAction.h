#pragma once

#include "Action.h"
#include <fstream>
using namespace std;
class SaveAction : public Action
{
	ofstream savefile;

public:
	SaveAction(ApplicationManager *pApp);
	~SaveAction();

	virtual void Execute();

	virtual void ReadActionParameters();



};

