#include "CCircle.h"

CCircle::CCircle(Point center, Point radiusPoint,GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this -> center = center;
	radius = sqrt(pow(radiusPoint.x - center.x, 2) + pow(radiusPoint.y - center.y, 2));
	
}
CCircle::CCircle(const CCircle& cpy):CFigure(cpy.FigGfxInfo) {
	center = cpy.center;
	radius = cpy.radius;
	Selected = cpy.Selected;
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawCirc(center, radius, FigGfxInfo, Selected);
}
/*
bool CCircle::isClicked(int x, int y)const{

	if (FigGfxInfo.isFilled) //if it's filled check inside and on border
		return clickedInside(x, y) || clickedOnBorder(x, y);


	return 	clickedOnBorder(x, y); //it's not filled then check only on border
}*/
/* ****************NOT ready yet*****************
bool CCircle::clickedInside(int x, int y)const {

	//the area of circle made from center to x,y is equal or less than the are of the figure
	//then it's inside the figure

	bool lessthan = pow(x - center.x, 2) + pow(y - center.y, 2) < radius*radius;
	//to avoid float compare error
	bool equal = fabs(pow(x - center.x, 2) + pow(y - center.y, 2) - radius*radius) < 1e-6;

	return lessthan || equal;
}

bool CCircle::clickedOnBorder(int x, int y)const {

	for (int i = 1; i <= FigGfxInfo.BorderWdth; i++) {
		//float radius = sqrt()
	}
	return 1;
}

*/