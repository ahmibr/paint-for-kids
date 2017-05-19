#ifndef ROTATEACTION_H
#define ROTATEACTION_H
#include "Action.h"
#include "../DataManager.h"

class RotateAction :public Action, public DataManager
{
	int rotate;
public:
	RotateAction(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
};

#endif