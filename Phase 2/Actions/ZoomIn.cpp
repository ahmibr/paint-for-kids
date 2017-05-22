#include "ZoomIn.h"

#include "../ApplicationManager.h"

#include "..\GUI\Output.h"

#include "SelectAction.h"

ZoomIn::ZoomIn(ApplicationManager * pApp) :Action(pApp), maxNumberOfZooms(5)
{
	numberOfZooms = 0;
}


ZoomIn::~ZoomIn()
{
}

//Execute the action
void ZoomIn::Execute()
{
	//Limit of the zoom
	if (UI.zoomFactor <= 1 + maxNumberOfZooms / 10.0f) {
		UI.zoomFactor += 0.1;
	}

	Output* pOut = pManager->GetOutput();

	pOut->UpdateZoomString();

	int size = 7;
	int *UnSupportedActions = new int[size];		//list of unsupported actions while zoom
	UnSupportedActions[0] = 0;
	UnSupportedActions[1] = 1;
	UnSupportedActions[2] = 2;
	UnSupportedActions[3] = 3;
	UnSupportedActions[4] = 10;
	UnSupportedActions[5] = 11;
	UnSupportedActions[6] = 12;

	if (UI.zoomFactor != 1)//bright icons only if we are on the right ratio
		pOut->dimIcons(UnSupportedActions, size);
	else
		pOut->brightIcons(UnSupportedActions, size);

	delete[] UnSupportedActions;
}

void ZoomIn::ReadActionParameters()
{
	//empty because not needed here
}

