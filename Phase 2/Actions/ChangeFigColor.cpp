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
	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	GfxInfo selectedColor;

	selectedColor.BorderWdth = pOut->getCrntPenWidth();
	selectedColor.FillClr = pOut->getCrntFillColor();
	selectedColor.DrawClr = pOut->getCrntDrawColor();
	selectedColor.isFilled = pOut->getCrntIsFilled();

	pIn->GraphicsInfo(selectedColor);

	UI.PenWidth = selectedColor.BorderWdth;
	UI.FillColor = selectedColor.FillClr;
	UI.DrawColor = selectedColor.DrawClr;

	for (int i = 0; i < pManager->GetFigureCount(); i++)
	{
		CFigure *curr = pManager->GetFigure(i);
		if (curr->IsSelected()) {
			curr->ChngDrawClr(UI.DrawColor);
			curr->ChngFillClr(UI.FillColor);
			curr->ChngBrdrWidth(UI.PenWidth);
		}
	}
}

void ChangeFigColor::ReadActionParameters()
{
	//empty because not needed here
}