#include "ResizeAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

class cFigures{};
ResizeAction::ResizeAction(ApplicationManager *pApp) :Action(pApp)
{
}

void ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	//include selectedFigureAction, get array of selectedfigures
	//if(selectedFiugures!=NULL)
		pOut->PrintMessage("Resize: choose for the new dimensions of selected figures");
		float Resize = pIn->Resize_wind();
		pOut->PrintMessage("Resize figure by " + to_string(Resize));
		/*for (int i = 0; i < selectedFigCount; i++)
		{
			if (dynamic_cast<CCircle*>(pFig[i]) )
				pFig[i]-> radius *=Resize; 

		    else if (dynamic_cast<CRectangle*>(pFig[i]))
			{
				pFig[i]->length *=Resize;     //added length & width to rect class
				pFig[i]->width *=Resize;
			}
			else if (dynamic_cast<CTriangle*>(pFig[i]))
			{
				pFig[i]->side1 *=Resize;
				pFig[i]->side2 *=Resize;     //added 3 sides of triangle
				pFig[i]->side3 *=Resize;
			}
			else if (dynamic_cast<Cline*>(pFig[i]))
			{
				pFig[i]->length *=Resize;   //added length of line
			}

		
		}*/
	
	//else pOut->PrintMessage("You should select at least one figure to Resize");
 
		//pOut->ClearStatusBar();
}

void ResizeAction::Execute()
{
	ReadActionParameters();
	//pFig[i]->draw();    loop to draw rsized figures
}


ResizeAction::~ResizeAction()
{
}
