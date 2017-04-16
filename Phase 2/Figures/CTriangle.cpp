#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2,Point P3,GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
	p3 = P3;

}
	
CTriangle::CTriangle(const CTriangle& cpy) :CFigure(cpy.FigGfxInfo) {
	p1 = cpy.p1;
	p2 = cpy.p2;
	p3 = cpy.p3;
	Selected = cpy.Selected;
}

CFigure* CTriangle::copyClone() {
	return new CTriangle(*this);	//make a new object and fill it with my data using copy constructor
									//then return it
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawTriangle to draw a triangle on the screen	
	pOut->DrawTriangle(p1, p2,p3, FigGfxInfo, Selected);
}

void CTriangle::Move(int dx, int dy) {
	p1.x += dx;
	p1.y += dy;
	p2.x += dx;
	p2.y += dy;
	p3.x += dx;
	p3.y += dy;
}

Point CTriangle::getPoint() const {
	return p1;
}