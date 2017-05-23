#ifndef CHANGE_FIG_COL
#define CHANGE_FIG_COL

#include "Action.h"

#include "..\Figures\CFigure.h"

class ChangeFigColor : public Action
{
	GfxInfo selectedColor;

	CFigure** selectedFigs;
	int selectedFigsCount;
	int *selectedFigsIds;

	GfxInfo prevInfo;
	GfxInfo currInfo;
public:
	ChangeFigColor(ApplicationManager *pApp);
	~ChangeFigColor();

	virtual void Execute();

	virtual void ReadActionParameters();

	void Undo();
	void Redo();


};

#endif