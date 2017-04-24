#include "CCircle.h"

CCircle::CCircle(Point center, Point radiusPoint, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	setPoints(center, radiusPoint);
}

void CCircle::setPoints(Point _center, Point _radiusPoint)
{
	center = _center;
	radius = sqrt(pow(_radiusPoint.x - _center.x, 2) + pow(_radiusPoint.y - _center.y, 2));
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

bool CCircle::isClicked(int x, int y)const {
	return clickedInside(x, y) || clickedOnBorder(x, y);
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


void CCircle::Move(int dx, int dy) {
	center.x += dx;	//change x by dx
	center.y += dy;	//change y by dy
}

Point CCircle::getPoint() const {
	return center;
}


string CCircle::printInfo()const {

	string data;
	data += "Circle: ID(" + to_string(ID) + ")"; //ID
	data += " ";
	data += "Center (" + to_string(center.x) + "," + to_string(center.y) + ")"; //center point
	data += " ";
	data += "Radius = " + to_string(radius); //radius
	data += " ";
	data += "Area = " + to_string(acos(-1)*radius*radius); //area PI*R*R
	return data; //return info about figure to be printed
}

void CCircle::Save(ofstream & OutFile)
{
	OutFile << "Circle  ";
	OutFile << ID << "  ";
	OutFile << center.x << "  ";
	OutFile << center.y << "  ";
	OutFile << radius << "  ";
	if (operator==(FigGfxInfo.DrawClr, sf::Color(0, 0, 0)))
		OutFile << "Black  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(255, 255, 255)))
		OutFile << "White  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(0, 255, 0)))
		OutFile << "Green  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(255, 0, 0)))
		OutFile << "Red  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(0, 0, 255)))
		OutFile << "Blue  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(0, 255, 127.5)))
		OutFile << "Turquoise  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(255, 255, 127.5)))
		OutFile << "Yellow  ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(255, 127.5, 0)))
		OutFile << "Orange  ";
	else
		OutFile << "Grey  ";
	if (!FigGfxInfo.isFilled)
		OutFile << "NO_Fill  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(0, 0, 0)))
		OutFile << "Black  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(255, 255, 255)))
		OutFile << "White  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(0, 255, 0)))
		OutFile << "Green  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(255, 0, 0)))
		OutFile << "Red  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(0, 0, 255)))
		OutFile << "Blue  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(0, 255, 127.5)))
		OutFile << "Turquoise  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(255, 255, 127.5)))
		OutFile << "Yellow  ";
	else if (operator==(FigGfxInfo.FillClr, sf::Color(255, 127.5, 0)))
		OutFile << "Orange  ";
	else
		OutFile << "Grey  ";
}
