#include "CLine.h"



CLine::CLine()
{
	length = 0;
}

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	setPoints(P1, P2);
}

void CLine::setPoints(Point _p1, Point _p2)
{
	if (_p1.x > _p2.x) //clicked right then left
		p1 = _p2, p2 = _p1;
	else //normal case;
		p1 = _p1, p2 = _p2;
	updateInfo();
}

void CLine::updateInfo()
{
	length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

CLine::CLine(const CLine& cpy) : CFigure(cpy.FigGfxInfo) {
	setPoints(cpy.p1, cpy.p2);
	Selected = cpy.Selected;
}

CFigure* CLine::copyClone() {

	return new CLine(*this);	//make a new object and fill it with my data using copy constructor
								//then return it
}

void CLine::Draw(Output* pOut) const
{
	Point drawingP1;
	drawingP1.x = (-UI.width / 2 + p1.x)* UI.zoomFactor + UI.width / 2;
	drawingP1.y = (-UI.height / 2 + p1.y)* UI.zoomFactor + UI.height / 2;

	Point drawingP2;
	drawingP2.x = (-UI.width / 2 + p2.x)* UI.zoomFactor + UI.width / 2;
	drawingP2.y = (-UI.height / 2 + p2.y)* UI.zoomFactor + UI.height / 2;

	GfxInfo drawingInfo = FigGfxInfo;
	drawingInfo.BorderWdth *= UI.zoomFactor;

	//Call Output::DrawLine to draw a line on the screen	
	if (visible)
		pOut->DrawLine(drawingP1, drawingP2, drawingInfo, Selected);
}

void CLine::Move(int dx, int dy) {
	p1.x += dx;
	p1.y += dy;
	p2.x += dx;
	p2.y += dy;
}

void CLine::Rotate(float rotate)
{
	float angle_alpha;//angle of line with x-axis

	Point midPoint;
	midPoint.x = (p1.x + p2.x) / 2;
	midPoint.y = (p1.y + p2.y) / 2;

	angle_alpha = atan2(p2.y - midPoint.y, p2.x - midPoint.x);

	float midLength = length / 2;
	Point p1Rotate, p2Rotate;
	p1Rotate.x = midPoint.x + midLength * cos(angle_alpha - rotate * (22.0 / (180 * 7)));
	p1Rotate.y = midPoint.y + midLength * sin(angle_alpha - rotate * (22.0 / (180 * 7)));

	p2Rotate.x = midPoint.x - midLength * cos(angle_alpha - rotate * (22.0 / (180 * 7)));
	p2Rotate.y = midPoint.y - midLength * sin(angle_alpha - rotate * (22.0 / (180 * 7)));

	setPoints(p1Rotate, p2Rotate);
}

void CLine::Resize(float size)
{
	float hight = fabs(p2.y - p1.y);
	float Long = fabs(p2.x - p1.x);
	float tempL = Long * size;
	float temph = hight * size;

	Point point1 = p1, point2 = p2;
	if (tempL < Long)
	{
		if (p2.x > p1.x && p2.y > p1.y) {
			point1.x += (Long*0.5 - tempL*0.5);
			point1.y += (hight*0.5 - temph*0.5);
			point2.x -= (Long*0.5 - tempL*0.5);
			point2.y -= (hight *0.5 - temph*0.5);
		}

		else if (p2.x > p1.x && p2.y < p1.y) {
			point1.x += (Long*0.5 - tempL*0.5);
			point1.y -= (hight*0.5 - temph*0.5);
			point2.x -= (Long*0.5 - tempL*0.5);
			point2.y += (hight *0.5 - temph*0.5);
		}

	}
	else if (tempL > Long)
	{
		if (p2.x > p1.x && p2.y > p1.y) {
			point1.x -= fabs((Long*0.5 - tempL*0.5));
			point1.y -= fabs((hight*0.5 - temph*0.5));
			point2.x += fabs((Long*0.5 - tempL*0.5));
			point2.y += fabs((hight *0.5 - temph*0.5));
		}
		else if (p2.x > p1.x && p2.y < p1.y) {
			point1.x -= fabs((Long*0.5 - tempL*0.5));
			point1.y += fabs((hight*0.5 - temph*0.5));
			point2.x += fabs((Long*0.5 - tempL*0.5));
			point2.y -= fabs((hight *0.5 - temph*0.5));
		}

	}
	setPoints(point1, point2);
}

Point CLine::getPoint() const {
	return p1;
}

float CLine::getArea() const
{
	return length;
}

string CLine::getType() const
{
	return "Line";
}

string CLine::getFillClrName() const
{
	return getDrawClrName();
}

bool CLine::isOutOfBorder(int dx, int dy) const
{
	return OutOfBorder(Point(p1.x + dx, p1.y + dy)) || OutOfBorder(Point(p2.x + dx, p2.y + dy));
}

bool CLine::isClicked(int x, int y) const {
	return clickedInside(x, y) && visible;
}

bool CLine::clickedInside(int x, int y) const
{
	//check length from p1-x and p2-x and compare it with p1-p2
	float check1 = sqrt(pow(p1.x - x, 2) + pow(p1.y - y, 2));
	float check2 = sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
	return fabs(check1 + check2 - length) <= FigGfxInfo.BorderWdth / 15.0; //add relative error for float comparison
}

bool CLine::clickedOnBorder(int x, int y) const
{
	//Empty function, just for Polymorphism
	return true;
}

string CLine::printInfo() const
{
	string data;
	data += "Line: ID(" + to_string(ID) + ")"; //ID
	data += " ";
	data += "Starting point (" + to_string(p1.x) + "," + to_string(p1.y) + ")"; //starting point
	data += " ";
	data += "Ending point (" + to_string(p2.x) + "," + to_string(p2.y) + ")"; //ending point
	data += " ";
	data += "Length = " + to_string(length); //length
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
	OutFile << FigGfxInfo.BorderWdth << "  ";
	OutFile << getDrawClrName() << "  ";
}

int CLine::getOriginXpos() {
	return (p1.x + p2.x) / 2;
}

int CLine::getOriginYpos() {
	return (p1.y + p2.y) / 2;
}

int CLine::getHeight() {
	return abs(p2.y - p1.y);
}

int CLine::getWidth() {
	return abs(p2.x - p1.x);
}

void CLine::setCurrCordTemp() {
	tempP1 = p1;
	tempP2 = p2;
}

void CLine::setTempCord() {
	setPoints(tempP1, tempP2);
}