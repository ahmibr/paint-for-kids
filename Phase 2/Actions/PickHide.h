#pragma once

#include "Action.h"
//Pick & Hide Action class
class PickHide : public Action
{
	int vCount, invCount, PickType, x, y, figures, pickedFigures;
	string str;
	void byType();
	void byColor();
	void byType_Color();
	void byArea();
	CFigure* current;
	CFigure* choosenFig;
	CFigure* fig;
public:
	PickHide(ApplicationManager *pApp);

	//Reads Pick & Hide parameters
	virtual void ReadActionParameters();

	//Add Pick & Hide to the ApplicationManager
	virtual void Execute();

	void Undo();
	void Redo();

};

