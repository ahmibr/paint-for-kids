#ifndef ZOOM_IN_CLASS
#define ZOOM_IN_CLASS

#include "Action.h"
#include "..\GUI\Output.h"

class ZoomIn : public Action
{
	const int maxNumberOfZooms;		//max number of zooms you can reach

	int numberOfZooms;				//number of current zooms

	void UpdateFigures(Output* pOut);

public:
	ZoomIn(ApplicationManager *pApp);
	~ZoomIn();

	virtual void Execute();

	virtual void ReadActionParameters();

};

#endif