#ifndef ROTATEACTION_H
#define ROTATEACTION_H
#include "Action.h"
#include "../DataManager.h"

class RotateAction:public Action,public DataManager
{
	bool selected;
public:
	RotateAction(ApplicationManager *pApp);
	virtual void Execute() ;
	virtual void ReadActionParameters();
};

#endif