#include "CFigure.h"

int CFigure::count = 0;

CFigure::CFigure()
{
	ID = ++count;
	Selected = false;
}

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

string CFigure::getDrawClrName() const
{
	if (FigGfxInfo.DrawClr == sf::Color(0, 0, 0))
		return "Black";
	else if (FigGfxInfo.DrawClr == sf::Color(255, 255, 255))
		return "White";
	else if (FigGfxInfo.DrawClr == sf::Color(0, 255, 0))
		return "Green";
	else if (FigGfxInfo.DrawClr == sf::Color(255, 0, 0))
		return "Red";
	else if (FigGfxInfo.DrawClr == sf::Color(0, 0, 255))
		return "Blue";
	else if (FigGfxInfo.DrawClr == sf::Color(0, 255, 127.5))
		return "Turquoise";
	else if (FigGfxInfo.DrawClr == sf::Color(255, 255, 127.5))
		return "Yellow";
	else if (FigGfxInfo.DrawClr == sf::Color(255, 127.5, 0))
		return "Orange";
	else
		return "Grey";
}

string CFigure::getFillClrName() const
{
	if (!FigGfxInfo.isFilled)
		return "NO_Fill";
	else if (FigGfxInfo.FillClr == sf::Color(0, 0, 0))
		return "Black";
	else if (FigGfxInfo.FillClr == sf::Color(255, 255, 255))
		return "White";
	else if (FigGfxInfo.FillClr == sf::Color(0, 255, 0))
		return "Green";
	else if (FigGfxInfo.FillClr == sf::Color(255, 0, 0))
		return "Red";
	else if (FigGfxInfo.FillClr == sf::Color(0, 0, 255))
		return "Blue";
	else if (FigGfxInfo.FillClr == sf::Color(0, 255, 127.5))
		return "Turquoise";
	else if (FigGfxInfo.FillClr == sf::Color(255, 255, 127.5))
		return "Yellow";
	else if (FigGfxInfo.FillClr == sf::Color(255, 127.5, 0))
		return "Orange";
	else
		return "Grey";
}

void CFigure::setVisible(bool visibilty)
{
	visible = visibilty;
}

bool CFigure::isVisible()
{
	return visible;
}