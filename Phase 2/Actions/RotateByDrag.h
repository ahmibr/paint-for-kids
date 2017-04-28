#ifndef ROTATE_BY_DRAG
#define ROTATE_BY_DRAG

#include "Action.h"

//Add Circle Action class
class RotateByDrag : public Action
{
private:
	int dx;
	float senstivity;//value of resize senstivity

public:
	RotateByDrag(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

};

#endif