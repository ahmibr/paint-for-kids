#include "ResizeAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

ResizeAction::ResizeAction(ApplicationManager *pApp) :Action(pApp)
{

}

void ResizeAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();

	resize = pIn->Resize_wind();
}

void ResizeAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	selectedFigs = pManager->getSelectedList(selectedFigsCount);
	//selectedFigs = pManager->CreateAcopyArray(selectedFigs, selectedFigsCount);
	selectedFigsIds = pManager->getIdArray(selectedFigs, selectedFigsCount);

	ReadActionParameters();
	if (resize)
	{
		if (pManager->ResizeFigures(resize))
			pOut->PrintMessage("Resize figures by " + to_string(resize));
		else
			pOut->PrintMessage("You should select at least one figure");
	}
}


ResizeAction::~ResizeAction()
{
	delete[] selectedFigsIds;
}

void ResizeAction::Undo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->ResizeFigures(1 / resize);
}

void ResizeAction::Redo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->ResizeFigures(resize);
}