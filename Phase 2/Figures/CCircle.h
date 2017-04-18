#ifndef CCirc_H
#define CCirc_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point center;
	float radius;
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
public:
	CCircle(Point , Point, GfxInfo FigureGfxInfo );
	CCircle(const CCircle&);//copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int y);
	virtual Point getPoint() const;		//get point to do some calculations
	virtual bool isClicked(int x, int y) const;//function to check if given point is related to the figure
	virtual string printInfo() const;
	virtual void Save(ofstream &OutFile); //Save Circle parameters to the file
};

#endif