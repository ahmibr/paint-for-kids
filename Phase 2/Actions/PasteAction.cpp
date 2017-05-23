#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "PasteAction.h"



PasteAction::PasteAction(ApplicationManager *pApp) :Action(pApp)
{
	able = true;
	inBorder = true;

	Undoable = false;
}

PasteAction::~PasteAction()
{
	for (int i = 0; i < oldClipBoard.size(); i++)
		delete oldClipBoard[i];
	oldClipBoard.clear();
}


void PasteAction::ReadActionParameters() {
	//get pointers to input and output class
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (!getSize()) //if the clipboard is empty, then nothing to be pasted
	{
		able = false;
		return;
	}
	int nx, ny;
	pOut->PrintMessage("Click where you want to paste");
	pIn->GetPointClicked(nx, ny); //get coordinates where user wants to paste
	CFigure* reference = clipBoard[0];  //take a reference to calibrate figures by it

	for (int i = 1; i < getSize(); i++)
		if (clipBoard[i]->getPoint().x < reference->getPoint().x) //take the left most figure
			reference = clipBoard[i];

	dx = nx - reference->getPoint().x; //get dx from nx and coordinates of left most figure
	dy = ny - reference->getPoint().y;	//get dy from ny and coordinates of left most figure

	for (int i = 0; i < getSize(); i++)
		if (clipBoard[i]->isOutOfBorder(dx, dy))
		{
			inBorder = false;
			break;
		}


	if (!able) {
		pOut->PrintMessage("Error! Out of border.");
		return;
	}
	pOut->PrintMessage("Paste is done succefully.");
}
//Execute the action
void PasteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (!inBorder)
		pOut->PrintMessage("Error! Out of border.");
	else if (!able)
		pOut->PrintMessage("Clipboard is empty!");
	else {
		pastedFigCount = getSize();
		pastedFigsIds = new int[pastedFigCount];
		Undoable = true;
		for (int i = 0; i < getSize(); i++)
		{
			pastedFigsIds[i] = clipBoard[i]->getID();
			clipBoard[i]->Move(dx, dy);
			pManager->AddFigure(clipBoard[i]);

			clipBoard[i] = clipBoard[i]->copyClone();//refresh the clipBoard (get new objects of old one)

			oldClipBoard.push_back(clipBoard[i]->copyClone()); //prepair to restore clipboard if undo is called
			oldClipBoard[i]->setID(pastedFigsIds[i]);
			CFigure::setCount(CFigure::getCount() - 1);
		}
		pOut->PrintMessage("Paste is done succefully.");
	}

}


void PasteAction::Undo() {
	Output* pOut = pManager->GetOutput();
	for (int i = 0; i < pastedFigCount; i++) //remove all pasted figures
		pManager->removeFigure(pastedFigsIds[i]);
	pOut->ClearStatusBar();

	pOut->PrintMessage("PasteAction Undone");
}

void PasteAction::Redo() {
	Output* pOut = pManager->GetOutput();
	for (int i = 0; i < pastedFigCount; i++) {
		pManager->AddFigure(oldClipBoard[i]);

		oldClipBoard[i] = oldClipBoard[i]->copyClone();
		oldClipBoard[i]->setID(pastedFigsIds[i]);
		CFigure::setCount(CFigure::getCount() - 1);
	}
	pManager->DeSelectAllFigures();
	pOut->ClearStatusBar();


	pOut->PrintMessage("PasteAction Redone");
}