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

	pOut->PrintMessage("Exit: Do you want to save ? Y or N");
	string choice = pIn->GetSrting(pOut);
	if (choice == "Y" || choice == "y")
		pManager->ExecuteAction(SAVE);

}

void ExitAction::Execute()
{
	//need only to read action parameters
	ReadActionParameters();

}


ExitAction::~ExitAction()
{
}
