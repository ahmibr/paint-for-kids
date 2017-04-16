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

CFigure* CRectangle::copyClone() {
	return new CRectangle(*this);	//make a new object and fill it with my data using copy constructor
									//then return it
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}


void CRectangle::Move(int dx, int dy) {
	Corner1.x += dx;
	Corner1.y += dy;
	Corner2.x += dx;
	Corner2.y += dy;
}

Point CRectangle::getPoint() const{
	return Corner1;
}