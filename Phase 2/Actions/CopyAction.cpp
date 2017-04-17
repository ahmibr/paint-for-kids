#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "CopyAction.h"



CopyAction::CopyAction(ApplicationManager *pApp) :Action(pApp)
{
}

//Execute the action
void CopyAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	bool selected = false;

	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		CFigure* curr = pManager->GetFigure(i);
		if (curr->IsSelected()) { //if current figure is selected
			if(!selected && getSize())	//if we found a selected element 
										//and clipBoard is not empty, then overlap happened
				destroyClipBoard();		//destroy the old clipBoard

			selected = true;
			CFigure* added = curr -> copyClone(); //get a copy of the current figure
			addToClipBoard(added); //add to to clipboard
		}
	}
	if (selected)
		pOut->PrintMessage("Copied to clipboard.");
	else
		pOut->PrintMessage("Select at least one shape.");
}

void CopyAction::ReadActionParameters()
{
}


