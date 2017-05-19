#include "ResizeAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

ResizeAction::ResizeAction(ApplicationManager *pApp) :Action(pApp)
{

}

void ResizeAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();

	resize = pIn->Resize_wind();
}

void ResizeAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();
	if (resize)
	{
		if (pManager->ResizeFigures(resize))
			pOut->PrintMessage("Resize figures by " + to_string(resize));
		else
			pOut->PrintMessage("You should select at least one figure");
	}
}


ResizeAction::~ResizeAction()
{
}
