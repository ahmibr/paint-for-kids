#include "ResizeByDrag.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ResizeByDrag::ResizeByDrag(ApplicationManager * pApp) :Action(pApp)
{
	senstivity = 50;
}

void ResizeByDrag::ReadActionParameters()
{

}

//Execute the action
void ResizeByDrag::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int xpos, ypos, lastXpos;//the current position of x,y and last pos
	float value;

	pOut->PrintMessage("Resizing selected objects.");

	pIn->GetPointClicked(xpos, ypos);
	lastXpos = xpos;//during the first frame xpos is the last

	while (xpos != -1) {

		dx = xpos - lastXpos;//dx is the change in x from current to last frame
		lastXpos = xpos;

		value = 1 + dx / senstivity;

		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {
				curr->Resize(value);
			}
		}

		pIn->GetMouseMove(xpos, ypos);

		pManager->UpdateInterface();
	}

	pOut->ClearStatusBar();
}
