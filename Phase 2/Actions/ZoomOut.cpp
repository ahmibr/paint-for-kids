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
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	do {

		pOut->PrintMessage("Zooming Out, Click AnyWhere to Exit");

		if (numberOfZooms < maxNumberOfZooms) {
			pOut->ZoomOut();
			numberOfZooms++;
		}

	} while (pIn->GetUserAction() == ZOOM_OUT);

	pOut->ClearStatusBar();
}

void ZoomOut::ReadActionParameters()
{
	//empty because not needed here
}