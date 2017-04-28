#ifndef RESIZE_BY_DRAG
#define RESIZE_BY_DRAG

#include "Action.h"

//Add Circle Action class
class ResizeByDrag : public Action
{
private:
	int dx;
	float senstivity;//value of resize senstivity

public:
	ResizeByDrag(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();

};

#endif