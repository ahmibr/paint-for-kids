#ifndef ROTATEACTION_H
#define ROTATEACTION_H
#include "Action.h"
#include "../DataManager.h"

class RotateAction :public Action, public DataManager
{
	int rotate;

	CFigure **selectedFigs;
	int selectedFigsCount;
	int *selectedFigsIds;
public:
	RotateAction(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	void Undo();
	void Redo();
};

#endif