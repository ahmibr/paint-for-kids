#ifndef ZOOM_IN_CLASS
#define ZOOM_IN_CLASS

#include "Action.h"
#include "..\GUI\Output.h"

class ZoomIn : public Action
{
	const int maxNumberOfZooms;		//max number of zooms you can reach

	int numberOfZooms;				//number of current zooms

public:
	ZoomIn(ApplicationManager *pApp);
	~ZoomIn();

	virtual void Execute();

	virtual void ReadActionParameters();

	void Undo();
	void Redo();

};

#endif