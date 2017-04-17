#include "..\Actions\SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SelectAction::SelectAction(ApplicationManager * pApp) :Action(pApp)
{
}

void SelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x = pIn->GetXmousePos();
	int y = pIn->GetYmousePos();
	pFigure = pManager->GetFigure(x, y);
}

//Execute the action
void SelectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	if (pFigure)
	{
		pFigure->SetSelected(!(pFigure->IsSelected()));
	}
	else
	{
		for (int i = 0; i < pManager->GetFigureCount(); i++)
			pManager->GetFigure(i)->SetSelected(false);
	}
}
