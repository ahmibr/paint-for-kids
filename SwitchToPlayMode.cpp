#include "SwitchToPlayMode.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToPlayMode::SwitchToPlayMode(ApplicationManager *pApp) :Action(pApp)
{
}

void SwitchToPlayMode::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Switch to play mode ");
	pOut->ClearDrawArea();                  //no clearing happens
	pOut->CreatePlayToolBar();
	
	//pOut->ClearStatusBar();

}

void SwitchToPlayMode::Execute()
{
	//need only to read action parameters
	ReadActionParameters();
}


SwitchToPlayMode::~SwitchToPlayMode()
{
}
