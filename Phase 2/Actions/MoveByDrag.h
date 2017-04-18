#ifndef MOVE_BY_DRAG
#define MOVE_BY_DRAG

#include "Action.h"

//Add Circle Action class
class MoveByDrag : public Action
{
private:
	int dx, dy;
public:
	MoveByDrag(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

};

#endif