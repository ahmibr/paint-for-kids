#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddCircleAction::AddCircleAction(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;
}

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

	//Newly Added
	int guideX, guideY;
	while (!pIn->GetMouseMoveNoHold(guideX, guideY) || (guideY < UI.ToolBarHeight || guideY > UI.height - UI.StatusBarHeight)) {
		float guideRadius = sqrt(pow(P1.x - guideX, 2) + pow(P1.y - guideY, 2));
		pOut->DrawGuideCircle(P1, guideRadius);
	}
	P2.x = guideX;
	P2.y = guideY;
	/////////////////////////////

	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();
	CircleGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	CircleGfxInfo.isFilled = pOut->getCrntIsFilled();

}

//Execute the action
void AddCircleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	float radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	Output* pOut = pManager->GetOutput();

	//Create a circle with the parameters read from the user
	C = new CCircle(P1, radius, CircleGfxInfo);

	if (C->isOutOfBorder()) {
		CFigure::setCount(CFigure::getCount() - 1); //as if the figure wasn't made
		delete C;	//deallocate unused memory
		pOut->PrintMessage("Error! Out of border");
		return;
	}

	FigureId = C->getID();

	//Add the circle to the list of figures
	pManager->AddFigure(C);

	pOut->PlayCircleSound();

	pOut->ClearStatusBar();
}

void AddCircleAction::Undo() {
	pManager->removeFigure(FigureId);

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Add AddCircleAction Undone");
}

void AddCircleAction::Redo() {

	int tempCount = CFigure::getCount();

	float radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	C = new CCircle(P1, radius, CircleGfxInfo);
	C->setID(FigureId);

	CFigure::setCount(tempCount);

	pManager->AddFigure(C);

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Add AddCircleAction Redone");
}