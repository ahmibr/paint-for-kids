#include "RotateByDrag.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


RotateByDrag::RotateByDrag(ApplicationManager * pApp) :Action(pApp)
{
	senstivity = 100000;
}

void RotateByDrag::ReadActionParameters()
{

}

//Execute the action
void RotateByDrag::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int xpos, ypos, lastXpos;//the current position of x,y and last pos
	float value;

	pOut->PrintMessage("Rotating selected objects.");

	pIn->GetPointClicked(xpos, ypos);
	lastXpos = xpos;//during the first frame xpos is the last

	while (xpos != -1) {

		dx = xpos - lastXpos;//dx is the change in x from current to last frame
		lastXpos = xpos;

		value = dx / senstivity;

		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {
				curr->Rotate(value);
			}
		}

		pIn->GetMouseMove(xpos, ypos);

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}
