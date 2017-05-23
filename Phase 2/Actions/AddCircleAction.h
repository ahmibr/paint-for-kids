#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"

#include "..\Figures\CCircle.h"

//Add Circle Action class
class AddCircleAction : public Action
{
private:
	Point P1, P2; //Circle points
	GfxInfo CircleGfxInfo;
	int FigureId;
	CCircle *C;
public:
	AddCircleAction(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

	void Undo();
	void Redo();

};

#endif