#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircleAction: public Action
{
private:
	Point P1, P2; //Circle points
	GfxInfo CircleGfxInfo;
	bool AddCircleAction::isOutOfBorder(Point p) const;
public:
	AddCircleAction(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();
	
	//Add circle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif