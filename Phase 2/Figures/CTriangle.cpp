#include "CTriangle.h"



CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	setPoints(P1, P2, P3);
}

void CTriangle::setPoints(Point _p1, Point _p2, Point _p3)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	updateInfo();
}

void CTriangle::updateInfo()
{
	lengthP1P2 = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	lengthP1P3 = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));

	lengthP2P3 = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));
}

CTriangle::CTriangle(const CTriangle& cpy) :CFigure(cpy.FigGfxInfo) {
	setPoints(cpy.p1, cpy.p2, cpy.p3);
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

void CTriangle::Rotate(float rotate) {

	Point orgin;
	Point point1, point2, point3;

	orgin.x = (p2.x + p3.x) / 2;
	orgin.x = (p1.x + orgin.x) / 2;
	orgin.y = (p2.y + p3.y) / 2;
	orgin.y = (p1.y + orgin.y) / 2;

	float op1, op2, op3;
	op1 = sqrt(pow(p1.x - orgin.x, 2) + pow(p1.y - orgin.y, 2));
	op2 = sqrt(pow(p2.x - orgin.x, 2) + pow(p2.y - orgin.y, 2));
	op3 = sqrt(pow(p3.x - orgin.x, 2) + pow(p3.y - orgin.y, 2));

	float angl1 = atan2((p1.y - orgin.y), (p1.x - orgin.x)) + rotate * 22.0 * (7.0 / 180);
	float angl2 = atan2((p2.y - orgin.y), (p2.x - orgin.x)) + rotate * 22.0 * (7.0 / 180);
	float angl3 = atan2((p3.y - orgin.y), (p3.x - orgin.x)) + rotate * 22.0 * (7.0 / 180);

	point1.x = ceil(orgin.x + op1*cos(angl1));
	point1.y = ceil(orgin.y + op1*sin(angl1));
	point2.x = ceil(orgin.x + op2*cos(angl2));
	point2.y = ceil(orgin.y + op2*sin(angl2));
	point3.x = ceil(orgin.x + op3*cos(angl3));
	point3.y = ceil(orgin.y + op3*sin(angl3));

	setPoints(point1, point2, point3);

}

void CTriangle::Resize(float size) {

	Point orgin;
	Point point1, point2, point3;

	orgin.x = ((p1.x + p2.x + p3.x) / 3);
	orgin.y = ((p1.y + p2.y + p3.y) / 3);

	float op1, op2, op3;
	op1 = sqrt(pow(p1.x - orgin.x, 2) + pow(p1.y - orgin.y, 2));
	op2 = sqrt(pow(p2.x - orgin.x, 2) + pow(p2.y - orgin.y, 2));
	op3 = sqrt(pow(p3.x - orgin.x, 2) + pow(p3.y - orgin.y, 2));

	float angl1 = atan2((p1.y - orgin.y), (p1.x - orgin.x));
	float angl2 = atan2((p2.y - orgin.y), (p2.x - orgin.x));
	float angl3 = atan2((p3.y - orgin.y), (p3.x - orgin.x));

	op1 *= size;
	op2 *= size;
	op3 *= size;

	point1.x = orgin.x + op1*cos(angl1);
	point1.y = orgin.y + op1*sin(angl1);
	point2.x = orgin.x + op2*cos(angl2);
	point2.y = orgin.y + op2*sin(angl2);
	point3.x = orgin.x + op3*cos(angl3);
	point3.y = orgin.y + op3*sin(angl3);

	setPoints(point1, point2, point3);

}

Point CTriangle::getPoint() const {
	return p1;
}

float CTriangle::getArea() const
{
	return area(p1, p2, p3);
}

string CTriangle::getType() const
{
	return "Triangle";
}

bool CTriangle::isClicked(int x, int y) const
{
	return clickedInside(x, y) || clickedOnBorder(x, y);
}

bool CTriangle::clickedInside(int x, int y) const
{
	//if sum of areas made from x,y to triangle points equal to the area of the triangle
	//as whole, then it's inside
	Point p; //to calculate area using 3 points
	p.x = x;
	p.y = y;

	//percentage error
	return fabs(area(p1, p2, p3) - area(p1, p2, p) - area(p2, p3, p) - area(p3, p1, p)) <= 0.5;
}

bool CTriangle::clickedOnBorder(int x, int y) const
{
	//check all lengthes of triangle, and check all lengthes made from x,y
	//to P1,P2,P3, if one is equal, then it's on border

	//length from x,y to p1
	float lengthXp1 = sqrt(pow(p1.x - x, 2) + pow(p1.y - y, 2));
	//length from x,y to p2
	float lengthXp2 = sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
	//length from x,y to p3
	float lengthXp3 = sqrt(pow(p3.x - x, 2) + pow(p3.y - y, 2));

	//side 1 (p1-p2)
	bool check1 = fabs(lengthP1P2 - lengthXp1 - lengthXp2) <= FigGfxInfo.BorderWdth / 10.0;
	//side 2 (p1-p3)
	bool check2 = fabs(lengthP1P3 - lengthXp1 - lengthXp3) <= FigGfxInfo.BorderWdth / 10.0;
	//side 3 (p2-p3)
	bool check3 = fabs(lengthP2P3 - lengthXp2 - lengthXp3) <= FigGfxInfo.BorderWdth / 10.0;

	return check1 || check2 || check3;
}

float CTriangle::area(Point p1, Point p2, Point p3)const
{
	//area by cross product
	return  fabs((p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x)) / 2;
}

string CTriangle::printInfo() const
{
	string data;
	data += "Traingle: ID(" + to_string(ID) + ")"; //ID
	data += " ";
	data += "P1 (" + to_string(p1.x) + "," + to_string(p1.y) + ")"; //starting point
	data += " ";
	data += "P2 (" + to_string(p2.x) + "," + to_string(p2.y) + ")"; //ending point
	data += " ";
	data += "P3 (" + to_string(p3.x) + "," + to_string(p3.y) + ")"; //ending point
	data += " ";
	data += "Area = " + to_string(getArea());
	return data; //return info about figure to be printed
}

void CTriangle::Save(ofstream & OutFile)
{
	OutFile << "Triangle  ";
	OutFile << ID << "  ";
	OutFile << p1.x << "  ";
	OutFile << p1.y << "  ";
	OutFile << p2.x << "  ";
	OutFile << p2.y << "  ";
	OutFile << p3.x << "  ";
	OutFile << p3.y << "  ";
	OutFile << FigGfxInfo.BorderWdth << "  ";
	OutFile << getDrawClrName() << "  ";
	OutFile << getFillClrName() << "  ";
}
