#include "..\Actions\SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager * pApp) :Action(pApp)
{
}

void SelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x = pIn->GetXmousePos();
	int y = pIn->GetYmousePos();
	pFigure = pManager->GetFigure(x, y);
}

//Execute the action
void SelectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	pManager->DeSelectAllFigures();

	if (pFigure) { //if he clicked on a figure, not an empty area
		pFigure->SetSelected(!(pFigure->IsSelected())); //toggle the state of figure
		if (pFigure->IsSelected())
			pOut->PrintMessage(pFigure->printInfo());
	}
	else
		pOut->ClearStatusBar();
}
