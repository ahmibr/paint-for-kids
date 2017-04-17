#include "CTriangle.h"



CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
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
	pOut->DrawTriangle(p1, p2, p3, FigGfxInfo, Selected);
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

bool CTriangle::isClicked(int x, int y) const
{
	return clickedInside(x, y);
}

bool CTriangle::clickedInside(int x, int y) const
{
	//if sum of areas made from x,y to triangle points equal to the area of the triangle
	//as whole, then it's inside
	Point p; //to calculate area using 3 points
	p.x = x;
	p.y = y;

	//percentage error
	return fabs(area(p1, p2, p3) - area(p1, p2, p) - area(p2, p3, p) - area(p3, p1, p)) <= FigGfxInfo.BorderWdth*150;
}

bool CTriangle::clickedOnBorder(int x, int y) const
{
	//Empty for polymorphism
	return true;
}

float CTriangle::area(Point p1, Point p2, Point p3)const
{
	//area by cross product
	return  fabs((p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x)) / 2;
}
