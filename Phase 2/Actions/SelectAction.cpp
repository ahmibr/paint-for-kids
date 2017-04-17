#include "..\Actions\SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager * pApp) :Action(pApp)
{
	numSelected = 0;
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

	//had to loop, because some actions (Delete, Cut, Paste)
	//interupts with number of selected items
	for (int i = 0; i < pManager->GetFigureCount(); i++) //get current count of selected items
		numSelected += pManager->GetFigure(i)->IsSelected();

	if (pFigure) //if he clicked on a figure, not an empty area
	{
		if (pFigure->IsSelected()) //if it's already selected before
			numSelected--;		//it'll be unselected, then decrease the counter
		else
			numSelected++; //it wasn't selected, then increase the counter

		pFigure->SetSelected(!(pFigure->IsSelected())); //toggle the state of figure

		if (numSelected == 1) //print states about figure
		{
			if (!pFigure->IsSelected()) //if the current click was to unselect a figure
				for (int i = 0; i < pManager->GetFigureCount(); i++)	//find the currently selected figure
					if (pManager->GetFigure(i)->IsSelected())
					{
						pFigure = pManager->GetFigure(i);
						break;
					}

			pOut->PrintMessage(pFigure->printInfo());
		}
		else if (numSelected > 1)
			pOut->PrintMessage("Number of Selected Items " + to_string(numSelected));
	}

	else //he clicked on empty area, then unselect all figures
	{
		for (int i = 0; i < pManager->GetFigureCount(); i++)
			pManager->GetFigure(i)->SetSelected(false);
		numSelected = 0;
	}

	if (!numSelected) //if no elements are currently selected at all
		pOut->ClearStatusBar();
}
