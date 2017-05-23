#include "MoveByDrag.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include "..\Figures\CFigure.h"

MoveByDrag::MoveByDrag(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;

	totalMovementX = 0;
	totalMovementY = 0;
}

MoveByDrag::~MoveByDrag()
{
	delete[] selectedFigsIds;
}

void MoveByDrag::ReadActionParameters()
{

}

//Execute the action
void MoveByDrag::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int xpos, ypos, lastXpos, lastYpos;//the current position of x,y and last pos

	pOut->PrintMessage("Dragging selected objects.");

	pIn->GetPointClicked(xpos, ypos);

	lastXpos = xpos;//during the first frame xpos is the last
	lastYpos = ypos;//during the first frame ypos is the last

	selectedFigs = pManager->getSelectedList(selectedFigsCount);
	//selectedFigs = pManager->CreateAcopyArray(selectedFigs, selectedFigsCount);
	selectedFigsIds = pManager->getIdArray(selectedFigs, selectedFigsCount);

	while (xpos != -1 && ypos != -1) {

		dx = xpos - lastXpos;//dx is the change in x from current to last frame
		dy = ypos - lastYpos;//dy is the change in y from current to last frame
		lastXpos = xpos;
		lastYpos = ypos;

		totalMovementX += dx;
		totalMovementY += dy;

		pManager->moveFigures(dx, dy);

		pIn->GetMouseMove(xpos, ypos);			//for more smoothness calling read action parameters is not prefarable

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}

void MoveByDrag::Undo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->moveFigures(-totalMovementX, -totalMovementY);
}

void MoveByDrag::Redo() {
	pManager->DeSelectAllFigures();

	for (int i = 0; i < selectedFigsCount; i++)
	{
		pManager->selectById(selectedFigsIds[i]);
	}

	pManager->moveFigures(totalMovementX, totalMovementY);
}