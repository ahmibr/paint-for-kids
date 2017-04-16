#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "PasteAction.h"



PasteAction::PasteAction(ApplicationManager *pApp) :Action(pApp)
{

}


void PasteAction::ReadActionParameters() {
	//get pointers to input and output class
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (!getSize()) //if the clipboard is empty, then nothing to be pasted
	{
		pOut->PrintMessage("Clipboard is empty!");
		return;
	}
	int nx, ny;
	pOut->PrintMessage("Click where you want to paste");
	pIn->GetPointClicked(nx, ny); //get coordinates where user wants to paste
	dx = nx - clipBoard[0]->getPoint().x; //get dx from nx and coordinates of first figure
	dy = ny - clipBoard[0]->getPoint().y;	//get dy from ny and coordinates of first figure
	pOut->PrintMessage("Paste is done succefully.");
}
//Execute the action
void PasteAction::Execute()
{
	ReadActionParameters();
	for (int i = 0; i < getSize(); i++)
	{
		clipBoard[i]->Move(dx, dy);
		pManager->AddFigure(clipBoard[i]);

		clipBoard[i] = clipBoard[i]->copyClone();//refresh the clipBoard (get new objects of old one)
	}

}


