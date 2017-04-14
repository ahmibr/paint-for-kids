#pragma once

#include"Action.h"
class SwitchToDrawMode :public Action
{
	
public:
	SwitchToDrawMode(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~SwitchToDrawMode();
};

