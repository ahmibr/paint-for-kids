#include "ChangeFigColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Output.h"


ChangeFigColor::ChangeFigColor(ApplicationManager * pApp) :Action(pApp)
{

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

	//previously written function that shows paleete and change the colors of upcoming
	pIn->GraphicsInfo(selectedColor);
}