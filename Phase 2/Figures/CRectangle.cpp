#include "CRectangle.h"

CRectangle::CRectangle()
{
	length = 0;
	width = 0;
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	setPoints(P1, P2);
}

void CRectangle::setPoints(Point P1, Point P2) {
	if (P2.x <= P1.x && P2.y <= P1.y) //in case pressed bottom right then top left
		Corner1 = P2, Corner2 = P1;
	else if (P1.x <= P2.x&&P1.y >= P2.y) //in case pressed bottom left then top right
		Corner1 = Point(P1.x, P2.y), Corner2 = Point(P2.x, P1.y);
	else if (P2.x <= P1.x&&P2.y >= P1.y) //in case pressed top right then bottom left
		Corner1 = Point(P2.x, P1.y), Corner2 = Point(P1.x, P2.y);
	else //normal case (top left then right bottom)
		Corner1 = P1, Corner2 = P2;
	updateInfo();
}

void CRectangle::updateInfo()
{
	length = Corner2.y - Corner1.y;
	width = Corner2.x - Corner1.x;
}

CRectangle::CRectangle(const CRectangle& cpy) :CFigure(cpy.FigGfxInfo) {
	setPoints(cpy.Corner1, cpy.Corner2);
	Selected = cpy.Selected;
}

CFigure* CRectangle::copyClone() {
	return new CRectangle(*this);	//make a new object and fill it with my data using copy constructor
									//then return it
}

void CRectangle::Draw(Output* pOut) const
{
	Point drawingCorner1;
	drawingCorner1.x = (-UI.width / 2 + Corner1.x)* UI.zoomFactor + UI.width / 2;
	drawingCorner1.y = (-UI.height / 2 + Corner1.y)* UI.zoomFactor + UI.height / 2;

	Point drawingCorner2;
	drawingCorner2.x = (-UI.width / 2 + Corner2.x)* UI.zoomFactor + UI.width / 2;
	drawingCorner2.y = (-UI.height / 2 + Corner2.y)* UI.zoomFactor + UI.height / 2;

	GfxInfo drawingInfo = FigGfxInfo;
	drawingInfo.BorderWdth *= UI.zoomFactor;

	//Call Output::DrawRect to draw a rectangle on the screen
	if (visible)
		pOut->DrawRect(drawingCorner1, drawingCorner2, drawingInfo, Selected);
}


void CRectangle::Move(int dx, int dy) {
	Corner1.x += dx;
	Corner1.y += dy;
	Corner2.x += dx;
	Corner2.y += dy;
}

void CRectangle::Resize(float size)
{

	float tempL = length * size;
	float tempW = width * size;

	Point p1 = Corner1, p2 = Corner2;
	if (tempL < length)
	{
		p1.x += (width*0.5 - tempW*0.5);
		p1.y += (length*0.5 - tempL*0.5);
		p2.x -= (width*0.5 - tempW*0.5);
		p2.y -= (length *0.5 - tempL*0.5);

	}
	else if (tempL > length)
	{
		p1.x -= fabs((width*0.5 - tempW*0.5));
		p1.y -= fabs((length*0.5 - tempL*0.5));
		p2.x += fabs((width*0.5 - tempW*0.5));
		p2.y += fabs((length *0.5 - tempL*0.5));

	}
	setPoints(p1, p2);

}

void CRectangle::Rotate(float rotate)
{
	float temp = fabs((length - width) / 2);
	Point p1 = Corner1, p2 = Corner2;

	if (rotate == 90 || rotate == 270)
	{
		if (length < width)
		{
			p1.x += temp;
			p1.y -= temp;
			p2.x -= temp;
			p2.y += temp;
		}
		else {
			p1.x -= temp;
			p1.y += temp;
			p2.x += temp;
			p2.y -= temp;
		}
	}
	else if (rotate == 180)
	{

	}
	setPoints(p1, p2);
}
Point CRectangle::getPoint() const {
	return Corner1;
}

float CRectangle::getArea() const
{
	return length*width;
}

string CRectangle::getType() const
{
	return "Rectangle";
}

bool CRectangle::isOutOfBorder(int dx, int dy) const
{
	return OutOfBorder(Point(Corner1.x + dx, Corner1.y + dy)) || OutOfBorder(Point(Corner2.x + dx, Corner2.y + dy));
}

bool CRectangle::isClicked(int x, int y) const {
	return (clickedInside(x, y) || clickedOnBorder(x, y)) && visible;
}

bool CRectangle::clickedInside(int x, int y) const {


	return (x >= Corner1.x && y >= Corner1.y && x <= Corner2.x && y <= Corner2.y);

}

bool CRectangle::clickedOnBorder(int x, int y) const {

	//Top Line
	float checktop1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner1.y - y, 2));
	float checktop2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner1.y - y, 2));
	bool top = fabs(width - checktop1 - checktop2) <= FigGfxInfo.BorderWdth / 15.0; //error percentage
	//Right Line
	float checkright1 = sqrt(pow(Corner2.x - x, 2) + pow(Corner1.y - y, 2));
	float checkright2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner2.y - y, 2));
	bool right = fabs(length - checkright1 - checkright2) <= FigGfxInfo.BorderWdth / 15.0;
	//Bottom Line
	float checkbot1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner2.y - y, 2));
	float checkbot2 = sqrt(pow(Corner2.x - x, 2) + pow(Corner2.y - y, 2));
	bool bot = fabs(width - checkbot1 - checkbot2) <= FigGfxInfo.BorderWdth / 15.0;
	//Left Line
	float checkleft1 = sqrt(pow(Corner1.x - x, 2) + pow(Corner1.y - y, 2));
	float checkleft2 = sqrt(pow(Corner1.x - x, 2) + pow(Corner2.y - y, 2));
	bool left = fabs(length - checkleft1 - checkleft2) <= FigGfxInfo.BorderWdth / 15.0;

	return top || bot || right || left;
}


string CRectangle::printInfo() const
{
	string data;
	data += "Rectangle: ID(" + to_string(ID) + ")"; //ID
	data += " ";
	data += "Corner1 (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")"; //starting point
	data += " ";
	data += "Corner2 (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")"; //ending point
	data += " ";
	data += "Hight = " + to_string(length);
	data += " ";
	data += "Width = " + to_string(width);
	data += " ";
	data += "Area = " + to_string(getArea());
	return data; //return info about figure to be printed
}

void CRectangle::Save(ofstream & OutFile)
{
	OutFile << "Rectangle  ";
	OutFile << ID << "  ";
	OutFile << Corner1.x << "  ";
	OutFile << Corner1.y << "  ";
	OutFile << Corner2.x << "  ";
	OutFile << Corner2.y << "  ";
	OutFile << FigGfxInfo.BorderWdth << "  ";
	OutFile << getDrawClrName() << "  ";
	OutFile << getFillClrName() << "  ";
}

void CRectangle::Load(ifstream & Infile)
{
	Infile >> ID;
	Infile >> Corner1.x;
	Infile >> Corner1.y;
	Infile >> Corner2.x;
	Infile >> Corner2.y;
	setPoints(Corner1, Corner2);
	Infile >> FigGfxInfo.BorderWdth;
	readColors(Infile, FigGfxInfo, false);
}

int CRectangle::getOriginXpos() {
	return (Corner1.x + Corner2.x) / 2;
}

int CRectangle::getOriginYpos() {
	return (Corner1.y + Corner2.y) / 2;
}

int CRectangle::getHeight() {
	return abs(Corner1.y - Corner2.y);
}

int CRectangle::getWidth() {
	return abs(Corner1.x - Corner2.x);
}

void CRectangle::setCurrCordTemp() {
	tempCorner1 = Corner1;
	tempCorner2 = Corner2;
}

void CRectangle::setTempCord() {
	setPoints(tempCorner1, tempCorner2);
}