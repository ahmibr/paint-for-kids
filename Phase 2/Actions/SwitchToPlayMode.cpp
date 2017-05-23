#include "SwitchToPlayMode.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToPlayMode::SwitchToPlayMode(ApplicationManager *pApp) :Action(pApp)
{
	Undoable = false;
}

void SwitchToPlayMode::ReadActionParameters()
{
	//no parameters to reads
}

void SwitchToPlayMode::Execute()
{
	Output* pOut = pManager->GetOutput();

	pManager->DeSelectAllFigures();

	UI.zoomFactor = 1;
	pOut->brightAllDrawIcons();

	pOut->CreatePlayToolBar();
	pOut->PrintMessage("Switch to play mode ");

}


SwitchToPlayMode::~SwitchToPlayMode()
{
}

void SwitchToPlayMode::Undo() {
}
void SwitchToPlayMode::Redo() {
}