#ifndef CUTACTION_H
#define CUTACTION_H
#include "Action.h"
#include "../DataManager.h"

class CutAction:public Action,public DataManager
{
	CFigure** selectedList;
	int selectedCount;
public:
	CutAction(ApplicationManager *pApp);
	virtual void Execute() ;
	virtual void ReadActionParameters();
};

#endif