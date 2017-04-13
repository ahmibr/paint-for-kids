#ifndef ZOOM_OUT_CLASS
#define ZOOM_OUT_CLASS

#include "Action.h"

class ZoomOut : public Action
{
	const int maxNumberOfZooms;		//max number of zooms you can reach

	int numberOfZooms;				//number of current zooms

public:
	ZoomOut(ApplicationManager *pApp);
	~ZoomOut();

	virtual void Execute();

	virtual void ReadActionParameters();



};

#endif