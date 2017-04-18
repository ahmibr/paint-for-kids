#include "CLine.h"



CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
}
CLine::CLine(const CLine& cpy) : CFigure(cpy.FigGfxInfo) {
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

bool CLine::isClicked(int x, int y) const {
	return clickedInside(x, y);
}

bool CLine::clickedInside(int x, int y) const
{
	//check length from p1-x and p2-x and compare it with p1-p2
	float length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	float check1 = sqrt(pow(p1.x - x, 2) + pow(p1.y - y, 2));
	float check2 = sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
	return fabs(check1 + check2 - length) <= FigGfxInfo.BorderWdth/15.0; //add relative error for float comparison
}

bool CLine::clickedOnBorder(int x, int y) const
{
	//Empty function, just for Polymorphism
	return true;
}

string CLine::printInfo() const
{
	string data;
	data += "Line: ID(" + to_string(ID)+")"; //ID
	data += " ";
	data += "Starting point (" + to_string(p1.x) + "," + to_string(p1.y) + ")"; //starting point
	data += " ";
	data += "Ending point (" + to_string(p2.x) + "," + to_string(p2.y) + ")"; //ending point
	
	return data; //return info about figure to be printed
}

void CLine::Save(ofstream & OutFile)
{
	OutFile << "Line  ";
	OutFile << ID << "  ";
	OutFile << p1.x << "  ";
	OutFile << p1.y << "  ";
	OutFile << p2.x << "  ";
	OutFile << p2.y << "  ";
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
		OutFile << "Yellow ";
	else if (operator==(FigGfxInfo.DrawClr, sf::Color(255, 127.5, 0)))
		OutFile << "Orange  ";
	else
		OutFile << "Grey  ";

}