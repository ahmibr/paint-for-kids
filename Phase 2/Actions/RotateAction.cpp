#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "RotateAction.h"



RotateAction::RotateAction(ApplicationManager *pApp) :Action(pApp)
{
	 selected = false;
}

//Execute the action
void RotateAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ReadActionParameters();

	if (selected)
	{
		int rotate = pIn->Rotate_wind();
		pOut->PrintMessage("Rotate figures by " + to_string(rotate));

		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {
			
				curr->Rotate(rotate);
				curr->Draw(pOut);    // to draw rotated figures
			}
		}
	}

}

void RotateAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		CFigure *curr = pManager->GetFigure(i);
		if (curr->IsSelected()) {
			selected = true;
			break;
		}
	}
	if (!selected)
		pOut->PrintMessage("You should select at least one figure");
	else
	{
		pOut->PrintMessage("Rotate: choose the angle to rotate selected figures");
	}

}


