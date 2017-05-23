#include "ChangeBkgroundClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


ChangeBkgroundClr::ChangeBkgroundClr(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;
}


ChangeBkgroundClr::~ChangeBkgroundClr()
{
}

//Execute the action
void ChangeBkgroundClr::Execute()
{
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	prevBckColor = UI.BkGrndColor;

	pIn->BackgrndColor();

	currBckColor = UI.BkGrndColor;

	pOut->PrintMessage("change background color successfully");
}

void ChangeBkgroundClr::ReadActionParameters()
{
	//empty because not needed here
}

void ChangeBkgroundClr::Undo() {
	UI.BkGrndColor = prevBckColor;

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("ChangeBkgroundClr Undone");
}

void ChangeBkgroundClr::Redo() {
	UI.BkGrndColor = currBckColor;

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("ChangeBkgroundClr Redone");
}