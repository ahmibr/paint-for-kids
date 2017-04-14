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
	virtual void Draw(Output* pOut) const;
};

#endif