#include "ZoomIn.h"

#include "../ApplicationManager.h"

#include "..\GUI\Output.h"


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
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	do {

		pOut->PrintMessage("Zooming In, Click AnyWhere to Exit");

		if (numberOfZooms < maxNumberOfZooms) {
			pOut->ZoomIn();
			numberOfZooms++;
		}

	} while (pIn->GetUserAction() == ZOOM_IN);

	pOut->ClearStatusBar();
}

void ZoomIn::ReadActionParameters()
{
	//empty because not needed here
}