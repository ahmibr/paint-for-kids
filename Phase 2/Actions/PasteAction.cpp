#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "PasteAction.h"



PasteAction::PasteAction(ApplicationManager *pApp) :Action(pApp)
{
	able = true;
	inBorder = true;
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
		for (int i = 0; i < getSize(); i++)
		{
			clipBoard[i]->Move(dx, dy);
			pManager->AddFigure(clipBoard[i]);

			clipBoard[i] = clipBoard[i]->copyClone();//refresh the clipBoard (get new objects of old one)
		}
		pOut->PrintMessage("Paste is done succefully.");
	}

}


