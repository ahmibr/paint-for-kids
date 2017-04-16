#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point p1;	
	Point p2;
public:
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	CLine(const CLine&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
};

#endif