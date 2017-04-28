#include "ChangeBkgroundClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


ChangeBkgroundClr::ChangeBkgroundClr(ApplicationManager * pApp) :Action(pApp)
{

}


ChangeBkgroundClr::~ChangeBkgroundClr()
{
}

//Execute the action
void ChangeBkgroundClr::Execute()
{
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	pIn->BackgrndColor();
	pOut->PrintMessage("change background color successfully");
}

void ChangeBkgroundClr::ReadActionParameters()
{
	//empty because not needed here
}