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
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTriangle(p1, p2,p3, FigGfxInfo, Selected);
}