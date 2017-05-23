#ifndef ADD_LINE_ACTION_H
#define ADD_LINE_ACTION_H

#include "Action.h"

#include "..\Figures\Cline.h"

//Add Rectangle Action class
class AddLineAction : public Action
{
private:
	Point P1, P2; //Line points
	GfxInfo LineGfxInfo;

	CLine *L;
public:
	AddLineAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();

	void Undo();
	void Redo();

};

#endif