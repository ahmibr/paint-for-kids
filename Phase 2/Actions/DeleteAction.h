#pragma once

#include"Action.h"

#include "..\Figures\CFigure.h"

class DeleteAction :public Action
{
	bool confirm;

	CFigure **deletedFigures;
	int deletedFigCount;
public:
	DeleteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~DeleteAction();
	void Undo();
	void Redo();
};

