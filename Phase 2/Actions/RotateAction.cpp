#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "RotateAction.h"



RotateAction::RotateAction(ApplicationManager *pApp) :Action(pApp)
{
	rotate = 0;
}

RotateAction::~RotateAction()
{
	delete[] selectedFigsIds;
}

//Execute the action
void RotateAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	selectedFigs = pManager->getSelectedList(selectedFigsCount);
	//selectedFigs = pManager->CreateAcopyArray(selectedFigs, selectedFigsCount);
	selectedFigsIds = pManager->getIdArray(selectedFigs, selectedFigsCount);

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


void RotateAction::Undo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->RotateFigures(360 - rotate);
}

void RotateAction::Redo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->RotateFigures(rotate);
}