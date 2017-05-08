#pragma once

#include"Action.h"
class PopMenu :public Action
{
	int action;
	int menuCornerX, menuCornerY;
public:
	PopMenu(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~PopMenu();
};

