#ifndef CHANGE_FIG_COL
#define CHANGE_FIG_COL

#include "Action.h"

class ChangeFigColor : public Action
{
	GfxInfo selectedColor;

public:
	ChangeFigColor(ApplicationManager *pApp);
	~ChangeFigColor();

	virtual void Execute();

	virtual void ReadActionParameters();


};

#endif