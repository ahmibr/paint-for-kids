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

void CFigure::setID(int _ID)
{
	if (_ID > 0) //only if valid ID. Otherwise, keep the current ID
	{
		if (count < _ID)
			count = _ID; //avoid next collision
		ID = _ID;
	}
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
	if (operator==(Fclr, sf::Color::Transparent))
		FigGfxInfo.isFilled = false;
	else
		FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

void CFigure::ChngBrdrWidth(int width)
{
	FigGfxInfo.BorderWdth = width;
}

