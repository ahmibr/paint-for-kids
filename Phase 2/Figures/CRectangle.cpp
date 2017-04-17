#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	if (Corner2.x <= Corner1.x && Corner2.y <= Corner1.y)
		swap(Corner1, Corner2);	//to make sure Corner 1 is upper left
}

CRectangle::CRectangle(const CRectangle& cpy) :CFigure(cpy.FigGfxInfo) {
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

Point CRectangle::getPoint() const {
	return Corner1;
}

bool CRectangle::isClicked(int x, int y) const {
	return clickedInside(x, y) || clickedOnBorder(x, y);
}

bool CRectangle::clickedInside(int x, int y) const {


	return (x >= Corner1.x && y >= Corner1.y && x <= Corner2.x && y <= Corner2.y);

}

bool CRectangle::clickedOnBorder(int x, int y) const {

	float lengthWide = sqrt(pow(Corner1.x - Corner2.x, 2));
	float lengthSide = sqrt(pow(Corner1.y - Corner2.y, 2));
	
	//Top Line
	float checktop1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner1.y - y, 2));
	float checktop2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner1.y - y, 2));
	bool top = fabs(lengthWide - checktop1 - checktop2) <= FigGfxInfo.BorderWdth / 15.0; //error percentage
	//Right Line
	float checkright1 = sqrt(pow(Corner2.x - x, 2) + pow(Corner1.y - y, 2));
	float checkright2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner2.y - y, 2));
	bool right = fabs(lengthSide - checkright1 - checkright2) <= FigGfxInfo.BorderWdth / 15.0;
	//Bottom Line
	float checkbot1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner2.y - y, 2));
	float checkbot2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner2.y - y, 2));
	bool bot = fabs(lengthWide - checkbot1 - checkbot2) <= FigGfxInfo.BorderWdth / 15.0;
	//Left Line
	float checkleft1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner1.y - y, 2));
	float checkleft2 = sqrt(pow(Corner1.x - x, 2) + pow(Corner2.y - y, 2));
	bool left = fabs(lengthSide - checkleft1 - checkleft2) <= FigGfxInfo.BorderWdth / 15.0;

	return top || bot || right || left;
}
