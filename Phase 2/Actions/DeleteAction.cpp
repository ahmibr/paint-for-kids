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

	pOut->PrintMessage("Delete: Are you sure you want to delete? Y or N");
	string choice = pIn->GetSrting(pOut);
	if (choice == "y" || choice == "Y")
		confirm = true;
	else
		pOut->ClearStatusBar();
}
void DeleteAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (confirm) {
		if (!pManager->DeleteFigures())
			pOut->PrintMessage("You should select at least one figure to delete");
		else
			pOut->PrintMessage("Deletion is done.");
	}
}


DeleteAction::~DeleteAction()
{
}
