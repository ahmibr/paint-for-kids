#include "ZoomOut.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


ZoomOut::ZoomOut(ApplicationManager * pApp) :Action(pApp), maxNumberOfZooms(3)
{
	numberOfZooms = 0;
}


ZoomOut::~ZoomOut()
{
}

//Execute the action
void ZoomOut::Execute()
{
	if (UI.zoomFactor >= 0.7) {
		UI.zoomFactor -= 0.1;
	}

	Output* pOut = pManager->GetOutput();

	int size = 7;
	int *UnSupportedActions = new int[size];
	UnSupportedActions[0] = 0;
	UnSupportedActions[1] = 1;
	UnSupportedActions[2] = 2;
	UnSupportedActions[3] = 3;
	UnSupportedActions[4] = 10;
	UnSupportedActions[5] = 11;
	UnSupportedActions[6] = 12;

	if (UI.zoomFactor != 1)
		pOut->dimIcons(UnSupportedActions, size);
	else
		pOut->brightIcons(UnSupportedActions, size);

	delete[] UnSupportedActions;
}

void ZoomOut::ReadActionParameters()
{
	//empty because not needed here
}