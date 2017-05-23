#pragma once

#include"Action.h"

#include "..\Figures\CFigure.h"

class ResizeAction :public Action
{
	bool selected;
	float resize;

	CFigure **selectedFigs;
	int selectedFigsCount;
	int *selectedFigsIds;
public:
	ResizeAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~ResizeAction();
	void Undo();
	void Redo();
};