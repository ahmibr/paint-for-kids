#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point p1;	
	Point p2;
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
public:
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	CLine(const CLine&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
	virtual bool isClicked(int x, int y) const;//function to check if given point is related to the figure
};

#endif