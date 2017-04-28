#ifndef CHANGE_BKground_COL
#define CHANGE_BKground_COL

#include "Action.h"

class ChangeBkgroundClr : public Action
{

public:
	ChangeBkgroundClr(ApplicationManager *pApp);
	~ChangeBkgroundClr();

	virtual void Execute();

	virtual void ReadActionParameters();


};

#endif