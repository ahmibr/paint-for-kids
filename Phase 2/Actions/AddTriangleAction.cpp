#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include<SFML\Audio.hpp>

AddTriangleAction::AddTriangleAction(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;
}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first point");
	do {
		//Read 1st corner and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);
	} while (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight);//needed check not to draw on status bar or tool bar

	int guideX, guideY;
	Point guide;
	while (!pIn->GetMouseMoveNoHold(guideX, guideY) || (guide.y < UI.ToolBarHeight || guide.y > UI.height - UI.StatusBarHeight))
	{
		guide.x = guideX;
		guide.y = guideY;
		pOut->DrawGuideTriangle(P1, guide, guide);
	}
	P2 = guide;

	while (!pIn->GetMouseMoveNoHold(guideX, guideY) || (guide.y < UI.ToolBarHeight || guide.y > UI.height - UI.StatusBarHeight))
	{
		guide.x = guideX;
		guide.y = guideY;
		pOut->DrawGuideTriangle(P1, P2, guide);
	}
	P3 = guide;

	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();
	TriangleGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	TriangleGfxInfo.isFilled = pOut->getCrntIsFilled();

}

//Execute the action
void AddTriangleAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a triangle with the parameters read from the user
	T = new CTriangle(P1, P2, P3, TriangleGfxInfo);

	//Add the triangle to the list of figures
	pManager->AddFigure(T);

	FigureId = T->getID();

	pOut->PlayTriangleSound();

	pOut->ClearStatusBar();

}

void AddTriangleAction::Undo() {
	pManager->removeFigure(FigureId);

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Add AddTriangleAction Undone");
}

void AddTriangleAction::Redo() {

	int tempCount = CFigure::getCount();

	T = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	T->setID(FigureId);

	CFigure::setCount(tempCount);

	pManager->AddFigure(T);

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Add AddTriangleAction Redone");
}