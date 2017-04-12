#ifndef ADD_Triangle_ACTION_H
#define ADD_Triangle_ACTION_H

#include "Action.h"

//Add Rectangle Action class
class AddTriangleAction: public Action
{
private:
	Point P1, P2,P3; //Rectangle Corners
	GfxInfo TriangleGfxInfo;
public:
	AddTriangleAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif