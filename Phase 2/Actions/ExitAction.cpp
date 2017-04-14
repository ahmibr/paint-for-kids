#include "ExitAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


ExitAction::ExitAction(ApplicationManager *pApp) :Action(pApp)
{
}

void ExitAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	/*if(!saveAction())
		pOut->PrintMessage("Exit: Do you want to save ? y or N");
	if (pIn->GetSrting(pOut) == "Y")
		saveAction();
	*/

	pOut->PrintMessage("Exit: Are you sure you want to exit? y or n");
	if (pIn->GetSrting(pOut) == "y")
	{
		pOut->ClearDrawArea();
		pOut->ClearStatusBar();
	}

	//else UndoAction();    to continue 
}

void ExitAction::Execute()
{
	//need only to read action parameters
	ReadActionParameters();
}


ExitAction::~ExitAction()
{
}
