#include "..\Actions\MultiSelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MultiSelectAction::MultiSelectAction(ApplicationManager * pApp) :Action(pApp)
{
	numSelected = 0;
}

void MultiSelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x = pIn->GetXmousePos();
	int y = pIn->GetYmousePos();
	pFigure = pManager->GetFigure(x, y);
}

//Execute the action
void MultiSelectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if (pFigure) //if he clicked on a figure, not an empty area. Else doesn't do anything
	{
		pFigure->SetSelected(!(pFigure->IsSelected())); //toggle the state of figure
		for (int i = 0; i < pManager->GetFigureCount(); i++) //get current count of selected items
		{
			numSelected += pManager->GetFigure(i)->IsSelected();
			if (numSelected == 1 && pManager->GetFigure(i)->IsSelected()) //if only one selected.if numselected increased than 1, it won't affect
				pFigure = pManager->GetFigure(i);
		}

		if (numSelected == 1)
			pOut->PrintMessage(pFigure->printInfo());
		else if (numSelected > 1)
			pOut->PrintMessage("Number of Selected Items " + to_string(numSelected));
		else
			pOut->ClearStatusBar();
	}
}
