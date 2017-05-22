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

	int xpos, ypos, lastXpos, lastYpos;//the current position of x,y and last pos

	pOut->PrintMessage("Dragging selected objects.");

	pIn->GetPointClicked(xpos, ypos);

	lastXpos = xpos;//during the first frame xpos is the last
	lastYpos = ypos;//during the first frame ypos is the last

	while (xpos != -1 && ypos != -1) {

		dx = xpos - lastXpos;//dx is the change in x from current to last frame
		dy = ypos - lastYpos;//dy is the change in y from current to last frame
		lastXpos = xpos;
		lastYpos = ypos;

		pManager->moveFigures(dx, dy);

		pIn->GetMouseMove(xpos, ypos);			//for more smoothness calling read action parameters is not prefarable

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}
