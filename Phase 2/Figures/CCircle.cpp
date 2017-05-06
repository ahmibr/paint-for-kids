#include "CCircle.h"

CCircle::CCircle()
{
	radius = 0;
}

CCircle::CCircle(Point center, float radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->center = center;
	this->radius = radius;
}

void CCircle::setRadius(float radius)
{
	if (radius > 0)
		this->radius = radius;
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
	if (visible)
		pOut->DrawCirc(center, radius, FigGfxInfo, Selected);
}

bool CCircle::isClicked(int x, int y)const {
	return (clickedInside(x, y) || clickedOnBorder(x, y)) && visible;
}

bool CCircle::clickedInside(int x, int y)const {

	//if the length made from center to x,y is less than the radius
	//then it clicked iside


	return pow(x - center.x, 2) + pow(y - center.y, 2) <= radius*radius;
}

bool CCircle::clickedOnBorder(int x, int y)const {
	//same as clicked inside but,
	//add availability of border width
	return fabs(sqrt(pow(x - center.x, 2) + pow(y - center.y, 2)) - radius) <= FigGfxInfo.BorderWdth;
}


void CCircle::Move(int dx, int dy) {
	center.x += dx;	//change x by dx
	center.y += dy;	//change y by dy
}

void CCircle::Rotate(float rotate) {
	//rotate circle by any angle will be as it is
}

void CCircle::Resize(float size) {
	float r = radius;
	r *= size;
	setRadius(r);
}

Point CCircle::getPoint() const {
	return center;
}

float CCircle::getArea() const
{
	//area PI*R*R
	return acos(-1)*radius*radius;
}

string CCircle::getType() const
{
	return "Circle";
}

bool CCircle::isOutOfBorder(int dx, int dy) const
{
	bool checkRange = OutOfBorder(Point(center.x + radius + dx, center.y + dy));
	checkRange = checkRange || OutOfBorder(Point(center.x - radius + dx, center.y + dy));
	checkRange = checkRange || OutOfBorder(Point(center.x + dx, center.y + radius + dy));
	checkRange = checkRange || OutOfBorder(Point(center.x + dx, center.y - radius + dy));
	return checkRange;
}


string CCircle::printInfo()const {

	string data;
	data += "Circle: ID(" + to_string(ID) + ")"; //ID
	data += " ";
	data += "Center (" + to_string(center.x) + "," + to_string(center.y) + ")"; //center point
	data += " ";
	data += "Radius = " + to_string(radius); //radius
	data += " ";
	data += "Area = " + to_string(getArea());
	return data; //return info about figure to be printed
}

void CCircle::Save(ofstream & OutFile)
{
	OutFile << "Circle  ";
	OutFile << ID << "  ";
	OutFile << center.x << "  ";
	OutFile << center.y << "  ";
	OutFile << radius << "  ";
	OutFile << FigGfxInfo.BorderWdth << "  ";
	OutFile << getDrawClrName() << "  ";
	OutFile << getFillClrName() << "  ";
}

int CCircle::getOriginXpos() {
	return center.x;
}

int CCircle::getOriginYpos() {
	return center.y;
}

int CCircle::getHeight() {
	return radius * 2;
}

int CCircle::getWidth() {
	return radius * 2;
}

void CCircle::setCurrCordTemp() {
	tempCenter = center;
	tempRaduis = radius;
}

void CCircle::setTempCord() {
	center = tempCenter;
	radius = tempRaduis;
}