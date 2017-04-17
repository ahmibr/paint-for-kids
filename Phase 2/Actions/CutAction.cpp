#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "CutAction.h"



CutAction::CutAction(ApplicationManager *pApp) :Action(pApp)
{
}

//Execute the action
void CutAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	bool selected = false;
	if (getSize()) //if clipBoard is not empty, then overlap happened
		destroyClipBoard(); //destroy the old clipBoard
	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		CFigure* curr = pManager->GetFigure(i);
		if (curr->IsSelected()) { //if current figure is selected
			if (!selected && getSize())	//if we found a selected element 
										//and clipBoard is not empty, then overlap happened
				destroyClipBoard();		//destroy the old clipBoard

			selected = true;
			CFigure* added = curr->copyClone(); //get a copy of the current figure
			addToClipBoard(added); //add to to clipboard
			pManager->removeFigure(curr->getID()); //remove the figure from figlist(cut operation)
			i--; //reduce counter because we deleted an element
		}
	}
	if (selected)
		pOut->PrintMessage("Cut to clipboard.");
	else
		pOut->PrintMessage("Select at least one shape.");
}

void CutAction::ReadActionParameters()
{
}


