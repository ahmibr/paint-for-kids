#ifndef PASTEACTION_H
#define PASTEACTION_H
#include "Action.h"
#include "../DataManager.h"

class PasteAction:public Action,public DataManager
{
	int dx,dy; //changes in coordinates
public:
	PasteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
	
};

#endif