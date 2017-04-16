#include "DeleteAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


DeleteAction::DeleteAction(ApplicationManager *pApp) :Action(pApp)
{
	confirm = false;
}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	bool selected = false;
	pOut->PrintMessage("Delete: Are you sure you want to delete? Y or N");
	string choice = pIn->GetSrting(pOut);
	if (choice == "y" || choice == "Y")
		confirm = true;
	else
		pOut->ClearStatusBar();
}
void DeleteAction::Execute()
{
	//need only to read action parameters
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (confirm) {
		bool selected = false;
		for (int i = 0; i < pManager->GetFigureCount(); i++)
		{
			CFigure *curr = pManager->GetFigure(i);
			if (curr->IsSelected()) {
				selected = true;
				pManager->removeFigure(curr->getID());
				i--;
			}
		}
		if (!selected)
			pOut->PrintMessage("You should select at least one figure to delete");
		else
			pOut->PrintMessage("Deletion is done.");
	}
}


DeleteAction::~DeleteAction()
{
}
