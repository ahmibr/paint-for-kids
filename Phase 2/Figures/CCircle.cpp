#include "CCircle.h"

CCircle::CCircle(Point center, Point radiusPoint,GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this -> center = center;
	radius = sqrt(pow(radiusPoint.x - center.x, 2) + pow(radiusPoint.y - center.y, 2));
	
}
	

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawCirc(center, radius, FigGfxInfo, Selected);
}