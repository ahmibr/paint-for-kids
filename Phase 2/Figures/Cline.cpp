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

CFigure* CLine::copyClone() {

	return new CLine(*this);	//make a new object and fill it with my data using copy constructor
								//then return it
}
void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a line on the screen	
	pOut->DrawLine(p1, p2, FigGfxInfo, Selected);
}

void CLine::Move(int dx, int dy) {
	p1.x += dx;
	p1.y += dy;
	p2.x += dx;
	p2.y += dy;
}

Point CLine::getPoint() const {
	return p1;
}