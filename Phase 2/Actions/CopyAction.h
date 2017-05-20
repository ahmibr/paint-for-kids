#ifndef COPYACTION_H
#define COPYACTION_H
#include "Action.h"
#include "../DataManager.h"

class CopyAction:public Action,public DataManager
{
	CFigure** selectedList;
	int selectedCount;
public:
	CopyAction(ApplicationManager *pApp);
	virtual void Execute() ;
	virtual void ReadActionParameters();
};

#endif