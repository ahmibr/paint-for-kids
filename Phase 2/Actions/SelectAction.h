#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"
//Add Circle Action class
class SelectAction: public Action
{
	CFigure* pFigure;
	int x;
	int y;
public:
	SelectAction(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();
	
	//Add circle to the ApplicationManager
	virtual void Execute() ;

	void Undo();

	void Redo();
	
};

#endif