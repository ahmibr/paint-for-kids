#pragma once

#include"Action.h"
class ResizeAction :public Action
{
	
public:
	ResizeAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~ResizeAction();
};

