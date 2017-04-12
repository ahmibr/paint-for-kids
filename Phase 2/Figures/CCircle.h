#ifndef CCirc_H
#define CCirc_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point center;
	float radius;
public:
	CCircle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
};

#endif