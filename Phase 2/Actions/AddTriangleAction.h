#ifndef ADD_Triangle_ACTION_H
#define ADD_Triangle_ACTION_H

#include "Action.h"

#include "..\Figures\CTriangle.h"

//Add Rectangle Action class
class AddTriangleAction : public Action
{
private:
	Point P1, P2, P3; //Rectangle Corners
	GfxInfo TriangleGfxInfo;
	int FigureId;
	CTriangle *T;
public:
	AddTriangleAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

	void Undo();
	void Redo();

};

#endif