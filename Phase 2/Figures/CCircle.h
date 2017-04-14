#ifndef CCirc_H
#define CCirc_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point center;
	float radius;
	//bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	//bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
public:
	CCircle(Point , Point, GfxInfo FigureGfxInfo );
	CCircle(const CCircle&);//copy constructor
	virtual void Draw(Output* pOut) const;
	//virtual bool isClicked(int x, int y) const;//function to check if given point is related to the figure
};

#endif