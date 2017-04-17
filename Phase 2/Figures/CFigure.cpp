#include "CFigure.h"

int CFigure::count = 0;
CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	ID = ++count;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

int CFigure::getID() {
	return ID;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

void CFigure::ChngDrawClr(sf::Color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(sf::Color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

void CFigure::ChngBrdrWidth(int width)
{
	FigGfxInfo.BorderWdth = width;
}

