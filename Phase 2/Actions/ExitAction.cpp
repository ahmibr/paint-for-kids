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


	if (pIn->confirmAction("Save before Exit"))
		pManager->ExecuteAction(SAVE); //execute save action before exit

}

void ExitAction::Execute()
{
	//need only to read action parameters
	ReadActionParameters();

}


ExitAction::~ExitAction()
{
}
