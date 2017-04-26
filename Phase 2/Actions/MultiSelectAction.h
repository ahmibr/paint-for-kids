#ifndef MULTI_SELECT_ACTION_H
#define MULTI_SELECT_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"
//Add Circle Action class
class MultiSelectAction: public Action
{
	CFigure* pFigure;
	int x;
	int y;
	int numSelected;
public:
	MultiSelectAction(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();
	
	//Add circle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif