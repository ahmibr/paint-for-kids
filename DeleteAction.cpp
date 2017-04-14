#include "DeleteAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


DeleteAction::DeleteAction(ApplicationManager *pApp) :Action(pApp)
{
}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	bool selected = false;
	pOut->PrintMessage("Delete: Are you sure you want to delete? y or n");
	pIn->GetSrting(pOut) ;

	/*if(selectFiguresAction()!=NULL)
	{
		selected = true;
		pOut->PrintMessage("Delete: Are you sure you want to delete? y or n");
		if (pIn->GetSrting(pOut) == "y")
		{
			for (int i = 0; i < selectedFigCount; i++)
			{
				delete pFig[i] ;
				pFig[i] = NULL
			}
		}
	}
	else pOut->PrintMessage("You should select at least one figure to delete");
	*/
	
	pOut->ClearStatusBar();
}

void DeleteAction::Execute()
{
	//need only to read action parameters
	ReadActionParameters();
}


DeleteAction::~DeleteAction()
{
}
