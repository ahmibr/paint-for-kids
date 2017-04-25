#pragma once

#include "Action.h"
#include <fstream>
using namespace std;
class LoadAction : public Action
{
	ifstream loadfile;
	void readColors(GfxInfo& GFX,bool isLine);
public:
	LoadAction(ApplicationManager *pApp);
	~LoadAction();

	virtual void Execute();

	virtual void ReadActionParameters();



};

