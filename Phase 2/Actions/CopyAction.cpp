#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "CopyAction.h"



CopyAction::CopyAction(ApplicationManager *pApp) :Action(pApp)
{
	selectedList = NULL;
	selectedCount = 0;
}

//Execute the action
void CopyAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	if (selectedCount) { //there are selected figures
		if (getSize())				//if clipBoard is not empty, then overlap will happen
			destroyClipBoard();		//destroy the old clipBoard
		for (int i = 0; i < selectedCount; i++)
		{
			CFigure* curr = selectedList[i];

			CFigure* added = curr->copyClone(); //get a copy of the current figure
			addToClipBoard(added);	//add it to to clipboard
		}

		pOut->PrintMessage("Copied to clipboard.");
	}
	else //no selected figures found
		pOut->PrintMessage("Select at least one shape.");
}

void CopyAction::ReadActionParameters()
{
	selectedList = pManager->getSelectedList(selectedCount);
}


