#include "SwitchToDrawMode.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToDrawMode::SwitchToDrawMode(ApplicationManager *pApp) :Action(pApp)
{
}

void SwitchToDrawMode::ReadActionParameters()
{
	//no parameters to read
}

void SwitchToDrawMode::Execute()
{
	Output* pOut = pManager->GetOutput();

	//load the original graph 
	pManager->ShowAllFigures();

	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Switch to Draw mode ");

}


SwitchToDrawMode::~SwitchToDrawMode()
{
}
