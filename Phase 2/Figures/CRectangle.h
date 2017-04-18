#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	//upper left
	Point Corner2;	//lower right
	virtual bool clickedInside(int x, int y) const;//utility function to check if clicked inside figure
	virtual bool clickedOnBorder(int x, int y) const;//utility function to check if clicked on border of figure
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	CRectangle(const CRectangle&); //copy constructor
	virtual CFigure* copyClone(); //a clone to apply polymorphism on copy construtors
	virtual void Draw(Output* pOut) const;
	virtual void Move(int dx, int dy);//move shape by dx and dy
	virtual Point getPoint() const;		//get point to do some calculations
	virtual bool isClicked(int x, int y) const;
	virtual string printInfo() const;
	virtual void Save(ofstream &OutFile); //Save Rectangle parameters to the file
};

#endif