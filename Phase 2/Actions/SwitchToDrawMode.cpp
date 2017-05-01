#include "SwitchToDrawMode.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToDrawMode::SwitchToDrawMode(ApplicationManager *pApp) :Action(pApp)
{
}

void SwitchToDrawMode::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//load the original graph 
	pOut->PrintMessage("Switch to Draw mode ");

	pManager->ShowAllFigures();

	pOut->CreateDrawToolBar();
	//pOut->ClearStatusBar();

}

void SwitchToDrawMode::Execute()
{
	//need only to read action parameters
	ReadActionParameters();
}


SwitchToDrawMode::~SwitchToDrawMode()
{
}
