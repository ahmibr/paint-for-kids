#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "CutAction.h"



CutAction::CutAction(ApplicationManager *pApp) :Action(pApp)
{
	selectedList = NULL;
	selectedCount = 0;
}

//Execute the action
void CutAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	if (selectedCount) {		//there are selected figures
		if (getSize())				//if clipBoard is not empty, then overlap will happen
			destroyClipBoard();		//destroy the old clipBoard
		for (int i = 0; i < selectedCount; i++)
		{
			CFigure* curr = selectedList[i];

			CFigure* added = curr->copyClone(); //get a copy of the current figure
			addToClipBoard(added); //add to to clipboard
			pManager->removeFigure(curr->getID()); //remove the figure from figlist(cut operation)
		}

		pOut->PrintMessage("Cut to clipboard.");
	}
	else //no selected figures found
		pOut->PrintMessage("Select at least one shape.");
}

void CutAction::ReadActionParameters()
{
	selectedList = pManager->getSelectedList(selectedCount);
}


