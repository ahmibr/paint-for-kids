#ifndef MOVE_BY_DRAG
#define MOVE_BY_DRAG

#include "Action.h"

#include "..\Figures\CFigure.h"

//Add Circle Action class
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

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

	void Undo();
	void Redo();

};

#endif