#ifndef CTRING_H
#define CTRING_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point p1;
	Point p2;
	Point p3;

public:
	CTriangle(Point , Point,Point,GfxInfo FigureGfxInfo);
	CTriangle(const CTriangle&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
};

#endif