#include "ChangeFigColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"

#include "..\Figures\CFigure.h"

ChangeFigColor::ChangeFigColor(ApplicationManager * pApp) :Action(pApp)
{
	Undoable = true;
}


ChangeFigColor::~ChangeFigColor()
{
}

//Execute the action
void ChangeFigColor::Execute()
{
	ReadActionParameters();

	bool foundSelected = pManager->ChangeSelectedColor(selectedColor);

	//if none found selected change the color of coming drawing colors
	if (!foundSelected) {
		UI.PenWidth = selectedColor.BorderWdth;
		UI.FillColor = selectedColor.FillClr;
		UI.DrawColor = selectedColor.DrawClr;

		selectedFigsCount = 0;
	}
	else {
		selectedFigs = pManager->getSelectedList(selectedFigsCount);
		//selectedFigs = pManager->CreateAcopyArray(selectedFigs, selectedFigsCount);
		selectedFigsIds = pManager->getIdArray(selectedFigs, selectedFigsCount);
	}
}

void ChangeFigColor::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	selectedColor.BorderWdth = pOut->getCrntPenWidth();
	selectedColor.FillClr = pOut->getCrntFillColor();
	selectedColor.DrawClr = pOut->getCrntDrawColor();
	selectedColor.isFilled = pOut->getCrntIsFilled();

	prevInfo = selectedColor;

	//previously written function that shows paleete and change the colors of upcoming
	pIn->GraphicsInfo(selectedColor);

	currInfo = selectedColor;
}

void ChangeFigColor::Undo() {
	pManager->DeSelectAllFigures();
	if (selectedFigsCount == 0) {
		UI.PenWidth = prevInfo.BorderWdth;
		UI.FillColor = prevInfo.FillClr;
		UI.DrawColor = prevInfo.DrawClr;
	}
	else {
		for (int i = 0; i < selectedFigsCount; i++)
		{
			pManager->selectById(selectedFigsIds[i]);
		}
	}
	pManager->ChangeSelectedColor(prevInfo);
}

void ChangeFigColor::Redo() {
	pManager->DeSelectAllFigures();
	if (selectedFigsCount == 0) {
		UI.PenWidth = currInfo.BorderWdth;
		UI.FillColor = currInfo.FillClr;
		UI.DrawColor = currInfo.DrawClr;
	}
	else {
		for (int i = 0; i < selectedFigsCount; i++)
		{
			pManager->selectById(selectedFigsIds[i]);
		}
	}
	pManager->ChangeSelectedColor(currInfo);
}