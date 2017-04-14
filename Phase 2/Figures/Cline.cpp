#include "CLine.h"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
}
CLine::CLine(const CLine& cpy): CFigure(cpy.FigGfxInfo) {
	p1 = cpy.p1;
	p2 = cpy.p2;
	Selected = cpy.Selected;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawLine(p1, p2, FigGfxInfo, Selected);
}