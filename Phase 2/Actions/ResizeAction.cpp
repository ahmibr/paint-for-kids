#include "ResizeAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

class cFigures {};
ResizeAction::ResizeAction(ApplicationManager *pApp) :Action(pApp)
{
	selected = false;
}

void ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
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
		pOut->PrintMessage("Resize: choose for the new dimensions of selected figures");
	}

}

void ResizeAction::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();
	if (selected)
	{
		float size = pIn->Resize_wind();
		pOut->PrintMessage("Resize figure by " + to_string(size));

		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {

				curr->Resize(size);
				curr->Draw(pOut);    // to draw resized figures
			}
		}
	}
	//pOut->ClearStatusBar();

}


ResizeAction::~ResizeAction()
{
}
