#pragma once

#include"Action.h"
class DeleteAction :public Action
{
	bool confirm;
public:
	DeleteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~DeleteAction();
};

