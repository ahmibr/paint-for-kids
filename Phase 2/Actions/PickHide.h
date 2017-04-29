#pragma once

#include "Action.h"
//Pick & Hide Action class
class PickHide : public Action
{
	int vCount, invCount, PickType, x, y;
	string str;
	bool byType();
	bool byColor();
	bool byType_Color();
	bool byArea();
	CFigure* current;
	CFigure* choosenFig;
public:
	PickHide(ApplicationManager *pApp);

	//Reads Pick & Hide parameters
	virtual void ReadActionParameters();

	//Add Pick & Hide to the ApplicationManager
	virtual void Execute();

};

