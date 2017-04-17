#ifndef CTRING_H
#define CTRING_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point p1;
	Point p2;
	Point p3;
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
	float area(Point, Point, Point) const; //utility function to check if point is inside
public:
	CTriangle(Point , Point,Point,GfxInfo FigureGfxInfo);
	CTriangle(const CTriangle&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
	virtual bool isClicked(int x, int y) const;
	virtual string printInfo() const;
};

#endif