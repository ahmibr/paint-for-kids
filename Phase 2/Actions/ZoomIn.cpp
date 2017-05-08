#include "ZoomIn.h"

#include "../ApplicationManager.h"

#include "..\GUI\Output.h"

#include "SelectAction.h"

void ZoomIn::UpdateFigures(Output * pOut) {
	pManager->UpdateInterface();
	for (int i = 0; i < numberOfZooms; i++)
	{
		pOut->ZoomIn();
	}
}

ZoomIn::ZoomIn(ApplicationManager * pApp) :Action(pApp), maxNumberOfZooms(3)
{
	numberOfZooms = 0;
}


ZoomIn::~ZoomIn()
{
}

//Execute the action
void ZoomIn::Execute()
{
	if (UI.zoomFactor <= 1.3) {
		UI.zoomFactor += 0.1;
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

void ZoomIn::ReadActionParameters()
{
	//empty because not needed here
}

