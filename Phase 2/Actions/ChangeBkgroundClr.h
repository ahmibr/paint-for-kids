#ifndef CHANGE_BKground_COL
#define CHANGE_BKground_COL

#include "Action.h"

class ChangeBkgroundClr : public Action
{
	sf::Color prevBckColor;
	sf::Color currBckColor;
public:
	ChangeBkgroundClr(ApplicationManager *pApp);
	~ChangeBkgroundClr();

	virtual void Execute();

	virtual void ReadActionParameters();

	void Undo();
	void Redo();


};

#endif