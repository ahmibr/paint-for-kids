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
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	ActionType action = ZOOM_IN;

	do {
		if (action == CHNG_DRAW_CLR) {
			pManager->ExecuteAction(action);
			UpdateFigures(pOut);
		}
		else if (action == CHNG_BK_CLR) {
			pManager->ExecuteAction(action);
			UpdateFigures(pOut);
		}
		else if (action == ZOOM_IN) {
			pOut->PrintMessage("Zooming In, Click AnyWhere to Exit");
			if (numberOfZooms < maxNumberOfZooms) {
				pOut->ZoomIn();
				numberOfZooms++;
			}
		}
		else
		{
			break;
		}

		action = pIn->GetUserAction();

	} while (true);

	pOut->ClearStatusBar();
}

void ZoomIn::ReadActionParameters()
{
	//empty because not needed here
}

