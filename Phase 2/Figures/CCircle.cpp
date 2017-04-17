#include "CCircle.h"

CCircle::CCircle(Point center, Point radiusPoint, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->center = center;
	radius = sqrt(pow(radiusPoint.x - center.x, 2) + pow(radiusPoint.y - center.y, 2));

}
CCircle::CCircle(const CCircle& cpy) :CFigure(cpy.FigGfxInfo) {
	center = cpy.center;
	radius = cpy.radius;
	Selected = cpy.Selected;
}

CFigure* CCircle::copyClone() {
	return new CCircle(*this);	//make a new object and fill it with my data using copy constructor
								//then return it
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCirc to draw a Circle on the screen	
	pOut->DrawCirc(center, radius, FigGfxInfo, Selected);
}

bool CCircle::clickedInside(int x, int y)const {

	//if the length made from center to x,y is less than the radius
	//then it clicked iside


	return pow(x - center.x, 2) + pow(y - center.y, 2) <= radius*radius;
}

bool CCircle::clickedOnBorder(int x, int y)const {
	//same as clicked inside but,
	//add availability of border width
	return fabs( sqrt(pow(x - center.x, 2) + pow(y - center.y, 2)) - radius) <= FigGfxInfo.BorderWdth;
}

bool CCircle::isClicked(int x, int y)const {
	return clickedInside(x, y) || clickedOnBorder(x, y);
}

void CCircle::Move(int dx, int dy) {
	center.x += dx;	//change x by dx
	center.y += dy;	//change y by dy
}

Point CCircle::getPoint() const {
	return center;
}