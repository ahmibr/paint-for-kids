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
		int selectedCount = pManager->getSelectedCount();

		if (selectedCount == 0) //no selected elements 
			pOut->ClearStatusBar();

		else if (selectedCount == 1) { //handle the case if there are 2 selected figures and user unselected one of them

			if (pFigure->IsSelected()) //the chosen figure is selected
				pOut->PrintMessage(pFigure->printInfo());

			else //the chosen figure is unselected, we need to get the real selected figure
			{
				int size = 1;
				CFigure** selectedList = pManager->getSelectedList(size); //get the real selected Figure
				pOut->PrintMessage(selectedList[0]->printInfo());
			}
		}
		else
			pOut->PrintMessage("Number of Selected Elements = " + to_string(selectedCount));
	}
}
