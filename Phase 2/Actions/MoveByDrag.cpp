#include "MoveByDrag.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


MoveByDrag::MoveByDrag(ApplicationManager * pApp) :Action(pApp)
{}

void MoveByDrag::ReadActionParameters()
{

}

//Execute the action
void MoveByDrag::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int xpos, ypos, lastXpos, lastYpos;

	pOut->PrintMessage("Dragging selected objects.");

	pIn->GetPointClicked(xpos, ypos);
	lastXpos = xpos;
	lastYpos = ypos;

	while (xpos != -1 && ypos != -1) {

		dx = xpos - lastXpos;
		dy = ypos - lastYpos;
		lastXpos = xpos;
		lastYpos = ypos;

		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {
				curr->Move(dx, dy);
			}
		}

		pIn->GetMouseMove(xpos, ypos);

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}
