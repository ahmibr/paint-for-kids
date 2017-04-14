#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

CRectangle::CRectangle(const CRectangle& cpy) :CFigure(cpy.FigGfxInfo){
	Corner1 = cpy.Corner1;
	Corner2 = cpy.Corner2;
	Selected = cpy.Selected;
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
