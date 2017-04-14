#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

void AddLineAction::ReadActionParameters()
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click at second point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	LineGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
/*	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	*/
	pOut->ClearStatusBar();

}

//Execute the action
void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a line with the parameters read from the user
	CLine *L=new CLine(P1, P2, LineGfxInfo);

	//Add the line to the list of figures
	pManager->AddFigure(L);
}
