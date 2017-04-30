#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddCircleAction::AddCircleAction(ApplicationManager * pApp) :Action(pApp)
{}

void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at center");

	do {
		//Read 1st point and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);
	} while (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight);//needed check not to draw on status bar or tool bar

	pOut->PrintMessage("New Circle: Click at radius");

	do {
		//Read 2nd point and store in point P2
		pIn->GetPointClicked(P2.x, P2.y);
	} while (P2.y < UI.ToolBarHeight || P2.y > UI.height - UI.StatusBarHeight);//needed check not to draw on status bar or tool bar
	//CircleGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface

	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();
	CircleGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	CircleGfxInfo.isFilled = pOut->getCrntIsFilled();


	pOut->ClearStatusBar();

}

//Execute the action
void AddCircleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	float radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	Output* pOut = pManager->GetOutput();
	bool checkRange = isOutOfBorder(Point(P1.x + radius, P1.y));
	checkRange = checkRange || isOutOfBorder(Point(P1.x - radius, P1.y));
	checkRange = checkRange || isOutOfBorder(Point(P1.x, P1.y + radius));
	checkRange = checkRange || isOutOfBorder(Point(P1.x, P1.y - radius));
	if (checkRange)
	{
		pOut->PrintMessage("Error! Out of border");
		return;
	}
	//Create a circle with the parameters read from the user
	CCircle *C = new CCircle(P1, radius, CircleGfxInfo);

	//Add the circle to the list of figures
	pManager->AddFigure(C);
}

bool AddCircleAction::isOutOfBorder(Point p) const
{
	return p.x<0 || p.x>UI.width || p.y<UI.ToolBarHeight || p.y>UI.height - UI.StatusBarHeight;
}