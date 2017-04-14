#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	CRectangle(const CRectangle&); //copy constructor
	virtual void Draw(Output* pOut) const;
	//virtual bool isClicked(int x, int y) const;
};

#endif