#ifndef MOVE_BY_DRAG
#define MOVE_BY_DRAG

#include "Action.h"

#include "..\Figures\CFigure.h"

class MoveByDrag : public Action
{
private:
	int dx, dy;

	int totalMovementX, totalMovementY;

	CFigure **selectedFigs;
	int selectedFigsCount;
	int *selectedFigsIds;
public:
	MoveByDrag(ApplicationManager *pApp);
	~MoveByDrag();
	virtual void ReadActionParameters();

	virtual void Execute();

	void Undo();
	void Redo();

};

#endif