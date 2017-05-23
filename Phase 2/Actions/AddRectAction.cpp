#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");

	do {
		//Read 1st corner and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);
	} while (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight);//needed check not to draw on status bar or tool bar

	pOut->PrintMessage("New Rectangle: Click at second corner");

	Point Guide;
	while (!pIn->GetMouseMoveNoHold(Guide.x, Guide.y) || (Guide.y < UI.ToolBarHeight || Guide.y > UI.height - UI.StatusBarHeight))
	{
		pOut->DrawGuideRectangle(P1, Guide);
	}
	P2 = Guide;

	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	RectGfxInfo.isFilled = pOut->getCrntIsFilled();

}

//Execute the action
void AddRectAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	R = new CRectangle(P1, P2, RectGfxInfo);

	FigureId = R->getID();

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);

	pOut->PlayRectangleSound();

	pOut->ClearStatusBar();

}

void AddRectAction::Undo() {
	pManager->removeFigure(FigureId);
}

void AddRectAction::Redo() {

	int tempCount = CFigure::getCount();

	R = new CRectangle(P1, P2, RectGfxInfo);
	R->setID(FigureId);

	CFigure::setCount(tempCount);

	pManager->AddFigure(R);
}