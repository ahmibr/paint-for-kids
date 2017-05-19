#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "RotateAction.h"



RotateAction::RotateAction(ApplicationManager *pApp) :Action(pApp)
{
	rotate = 0;
}

//Execute the action
void RotateAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	if (rotate)
	{
		if (pManager->RotateFigures(rotate))
			pOut->PrintMessage("Rotate figures by " + to_string(rotate));

		else
			pOut->PrintMessage("You should select at least one figure");

	}

}

void RotateAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	rotate = pIn->Rotate_wind();
}